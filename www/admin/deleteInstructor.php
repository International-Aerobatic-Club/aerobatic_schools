<?php
set_include_path('../include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/dbCommand.inc");
require_once("toolkit/redirect.inc");
require_once('toolkit/encodeSQL.inc');
require_once('toolkit/encodeHTML.inc');
require_once("model/data.inc");

$wasUpdated = FALSE;
$readRecord = TRUE;
$corrMsg = '';
$db_conn = false;
$schoolID = '';
$instructorID = '';
$dbResult = '';
$fail = dbConnect($db_conn);
if ($fail != '')
{
   notifyError($fail, "deleteInstructor.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
   $readRecord = FALSE;
}
else if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   //   debugArr('delete instructor post', $_POST);
   // begin form processing
   if (isSet($_POST['instrId']))
   {
      $instructorID = $_POST['instrId'];
      $schoolID = $_POST['schoolId'];
      $query = "delete from instructor where id=" . intSQL($instructorID);
      $fail =  dbExec($db_conn, $query);
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "deleteInstructor.php");
         $corrMsg = "<it>Internal: failed delete.</it>";
      }
   }
   else
   {
      $corrMsg = 'Delete Instructor requires instructor id';
   }
}
if ($readRecord)
{
   // not POST
   $instructorID = $_GET['id'];
   //   debug('deleteInstructor id is '.$instructorID);
   if (isSet($instructorID))
   {
      // is delete for instructor with given id
      $query = 'select a.name, a.airCity, a.airState, a.country, b.schoolID, b.givenName, b.sirName' .
      ' from school a, instructor b where b.id = '.intSQL($instructorID).' and a.id = b.schoolId';
      $dbResult = dbQuery($db_conn, $query);
      if ($dbResult == FALSE)
      {
         notifyError('Failed query schools '.dbErrorText(), 'deleteInstructor.php');
         $corrMsg = "<li>Internal: failed query schools</li>";
      }
   }
   else
   {
      $corrMsg = 'Delete Instructor requires instructor id';
   }
}
dbClose($db_conn);
// Redirect logic
if ($wasUpdated)
{
   $nextURL = "index.php#".schoolAnchor($schoolID);
   getNextPage($nextURL);
}
else
{
   startHead("Delete Instructor");
   startContent();
   if ($corrMsg != '')
   {
      echo '<ul class="error">'.$corrMsg.'</ul>';
   }
   else
   {
      $rcd = dbFetchAssoc($dbResult);
      $schoolID = $rcd['schoolID'];
      echo "<div class='schoolName'>".strhtml($rcd['name'])."</div>\n";
      echo "<div class='schoolAddress'>";
      echo strhtml(displayLoc($rcd['airCity'],$rcd['airState'],$rcd['country']));
      echo "</div>\n";
      $instructorName = strhtml($rcd['givenName']).' '.strhtml($rcd['sirName']);
      echo "<div class='instructorName'>".$instructorName."</div>";
      echo '<form class="recordForm" action="deleteInstructor.php" method="post">';
      echo '<input name="instrId" type="hidden" value="'.$instructorID.'"/>';
      echo '<input name="schoolId" type="hidden" value="'.$schoolID.'"/>';
      echo '<div class="submit">';
      echo '<input class="submit" name="submit" type="submit" value="Delete Instructor '.$instructorName.'"/>';
      echo '</div>';
      echo '<div class="returnButton"><a href="index.php#'.instructorAnchor($instructorID).'">Return without deleting</a></div>';
   }
   endContent();
}
?>
