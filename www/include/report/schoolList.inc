<?php
require_once('toolkit/useful.inc');
require_once('toolkit/encodeHTML.inc');
require_once('toolkit/dbCommand.inc');
require_once('model/school.inc');
require_once('model/data.inc');

function doSchoolList($db_conn, $filter = '', $showActions = FALSE)
{
   $corrMsg = '';
   $dbResult = querySchools($db_conn, $filter);
   if ($dbResult == FALSE)
   {
      notifyError('Failed query schools '.dbErrorText(), 'schoolList.inc');
      $corrMsg = "<li>Internal: failed query schools</li>";
   }
   if ($corrMsg == '')
   {
      formatSchoolList($dbResult, $showActions);
   }
   return $corrMsg;
}

function querySchools($db_conn, $filter = '')
{
   $query = "select a.*, b.id as iid, b.givenName, b.sirName, b.cert, b.isACE from school a left outer join instructor b on b.schoolID = a.id";
   if ($filter != '')
   {
      $query .= ' where '. $filter;
   }
   $query .= ' order by a.country, a.airState, a.airport, a.name';
   debug('Schools query is ' . $query);
   return dbQuery($db_conn, $query);
}

function formatSchoolList($dbResult, $showActions=FALSE)
{
   $rcd = dbFetchAssoc($dbResult);
   $lastSchoolID = 0;
   $lastState = '';
   $haveInstructor = FALSE;
   while ($rcd)
   {
      //debugArr('schoolList record',$rcd);
      $id = $rcd['id'];
      if ($id != $lastSchoolID)
      {
         if ($lastSchoolID != 0) {
            endInstructorList($showActions, $lastSchoolID, $haveInstructor);
            $haveInstructor = false;
         }
         $lastSchoolID = $id;
         $lastState = checkDoStateHeading($rcd, $lastState);
         echo "<a name='".schoolAnchor($rcd['id'])."'/>\n";
         echo "<div class='schoolRecord'>\n";
         if ($showActions)
         {
            echo "<div class='schoolActions'>\n";
            echo "<a href='editSchool.php?id=".$rcd['id']."'>edit</a>\n";
            echo "<a href='deleteSchool.php?id=".$rcd['id']."'>delete</a>\n";
            echo "</div>\n";
         }
         displaySchoolRecord($rcd);
         if (isSet($rcd['iid']))
         {
            echo "<div class='instructorList'>\n";
            echo "<div class='schoolHeading'>Instructors:</div>\n";
            $haveInstructor = TRUE;
         }
      }
      if (isSet($rcd['iid']))
      {
         formatInstructor($rcd, $showActions);
      }
      $rcd = dbFetchAssoc($dbResult);
   }
   if ($lastSchoolID != 0) endInstructorList($showActions, $lastSchoolID, $haveInstructor);
}

function endInstructorList($showActions, $id, $haveInstructor)
{
   if ($haveInstructor) echo "</div>\n";
   if ($showActions){
      echo "<a href='editInstructor.php?schoolID=".$id."'>add instructor</a>\n";
   }
   echo "</div>\n";
}

function doWeb($web)
{
   $i = strpos($web,'http');
   if ($i === false)
   {
      $url = 'http://'.$web;
   }
   else
   {
      $url = substr($web,$i);
      $web = substr($web,5);
      $i = 0;
      while (strpos($web,'/',$i) === $i) ++ $i;
      $r = strlen($web) - 1;
      while (strrpos($web,'/',$r) === $r) -- $r;
      $web = substr($web, $i, ($r - $i + 1));
   }
   if (strrpos($url,'/') != strlen($url)-1)
   {
      $url .= '/';
   }
   return "<a href='$url'>$web</a>";
}

function doEmail($email)
{
   return "<a href='mailto:$email?subject=Aerobatic Schools Listing'>$email</a>";
}

function displaySchoolRecord($rcd)
{
   echo "<span class='schoolName'>".strhtml($rcd['name'])."</span>\n";
   echo "<span class='schoolAddress'>".strhtml($rcd['airport']);
   if ($rcd['airport'] != '') echo ' - ';
   echo strhtml(displayLoc($rcd['airCity'], $rcd['airState'], $rcd['country']));
   echo "</span>\n";
   echo "<div class='schoolContact'>\n";
   echo "<span class='schoolContactName'>".strhtml($rcd['contact']).".</span>\n";
   echo "<span class='schoolContactPhone'>Phone:&nbsp;".strhtml($rcd['phone'])."</span>";
   if (isSet($rcd['fax'])) echo "<span class='schoolContactFax'>Fax:&nbsp;".strhtml($rcd['fax'])."</span>";
   echo "<span class='schoolContactEmail'>Email:&nbsp;".doEmail(strhtml($rcd['email']))."</span>";
   if (isSet($rcd['web'])) echo "<span class='schoolContactWeb'>Web:&nbsp;".doWeb(strhtml($rcd['web']))."</span>";
   echo "</div>\n";
   if ($rcd['aircraft'] != '')
   {
      echo "<div class='schoolAircraft'>";
      echo "<div class='schoolHeading'>Aircraft:</div>";
      echo strhtml(strhtml($rcd['aircraft']));
      echo "</div>\n";
   }
   $firstCourse = true;
   $courses = School::courseValueDescription(strhtml($rcd['course']));
   foreach ($courses as $crs)
   {
      if ($firstCourse) {
         echo "<div class='schoolCourses'>\n";
         echo "<div class='schoolHeading'>Courses:</div>";
         $firstCourse = FALSE;
      }
      else { echo ', '; }
      echo "<span class='schoolCourse'>".strhtml($crs)."</span>";
   }
   if (!$firstCourse) {
      echo "</div>\n";
   }
   if ($rcd['notes'] != '')
   {
      echo "<div class='schoolNotes'>";
      echo strhtml($rcd['notes']);
      echo "</div>\n";
   }
}

function formatInstructor($rcd, $showActions)
{
   echo "<a name='".instructorAnchor($rcd['iid'])."'/>";
   echo "<div class='instructorRecord'>\n";
   if ($showActions)
   {
      echo "<div class='instructorActions'>\n";
      echo "<a href='editInstructor.php?id=".$rcd['iid']."'>edit</a>\n";
      echo "<a href='deleteInstructor.php?id=".$rcd['iid']."'>delete</a>\n";
      echo "</div>\n";
   }
   displayInstructorRecord($rcd);
   echo "</div>";
}

function displayInstructorRecord($rcd)
{
   echo "<span class='instructorName'>".strhtml($rcd['givenName']).' '.strhtml($rcd['sirName'])."</span>";
   if ($rcd['cert'] != 'none' || $rcd['isACE'] == 'y')
   {
      echo "<span class='instructorCred'>";
      $doComma = FALSE;
      if ($rcd['cert'] != 'none') {
         echo strhtml($rcd['cert']);
         $doComma = TRUE;
      }
      if ($rcd['isACE'] == 'y')
      {
         if ($doComma) echo ', ';
         echo 'A.C.E.';
      }
      echo "</span>";
   }
}

function checkDoStateHeading($rcd, $lastState)
{
   $state = strhtml($rcd['airState']);
   $country = strhtml($rcd['country']);
   $anchor = stateAnchor($state, $country);
   if ($anchor != $lastState)
   {
      echo "<a name='".$anchor."'/>";
      echo "<div class='state'>".displayLoc('', $state, $country);
      echo "<a class='top' href='#top'>(return to top)</a></div>\n";
   }
   return $anchor;
}

?>