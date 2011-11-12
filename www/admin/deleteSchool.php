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
$anchor = '';
$dbResult = '';
$fail = dbConnect($db_conn);
if ($fail != '')
{
   notifyError($fail, "deleteSchool.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
   $readRecord = FALSE;
}
else if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   //   debugArr('delete school post', $_POST);
   // begin form processing
   if (isSet($_POST['schoolId']))
   {
      $schoolID = $_POST['schoolId'];
      $anchor = $_POST['anchor'];
      $query = "delete from instructor where schoolId=" . intSQL($schoolID);
      $fail =  dbExec($db_conn, $query);
      if ($fail == '')
      {
         $query = "delete from school where id=" . intSQL($schoolID);
         $fail =  dbExec($db_conn, $query);
      }
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "deleteSchool.php");
         $corrMsg = "<it>Internal: failed delete.</it>";
      }
   }
   else
   {
      $corrMsg = 'Delete school requires school id';
   }
}
if ($readRecord)
{
   // not POST
   $schoolID = $_GET['id'];
   //   debug('deleteSchool id is '.$schoolID);
   if (isSet($schoolID))
   {
      // is delete for school with given id
      $query = 'select name, airCity, airState, country' .
      ' from school where id = '.intSQL($schoolID);
      $dbResult = dbQuery($db_conn, $query);
      if ($dbResult == FALSE)
      {
         notifyError('Failed query schools '.dbErrorText(), 'deleteSchool.php');
         $corrMsg = "<li>Internal: failed query schools</li>";
      }
   }
   else
   {
      $corrMsg = 'Delete school requires school id';
   }
}
dbClose($db_conn);
// Redirect logic
if ($wasUpdated)
{
   $nextURL = "index.php#".strhtml($anchor);
   getNextPage($nextURL);
}
else
{
   startHead("Delete School");
   startContent();
   if ($corrMsg != '')
   {
      echo '<ul class="error">'.$corrMsg.'</ul>';
   }
   else
   {
      $rcd = dbFetchAssoc($dbResult);
      $city = strhtml($rcd['airCity']);
      $state = strhtml($rcd['airState']);
      $country = strhtml($rcd['country']);
      $name = strhtml($rcd['name']);
      echo "<div class='schoolName'>".$name."</div>\n";
      echo "<div class='schoolAddress'>";
      echo displayLoc($city, $state, $country);
      echo "</div>\n";
      echo '<form class="recordForm" action="deleteSchool.php" method="post">';
      echo '<input name="schoolId" type="hidden" value="'.strhtml($schoolID).'"/>';
      echo '<input name="anchor" type="hidden" value="'.strhtml(stateAnchor($state, $country)).'"/>';
      echo '<div class="submit">';
      echo '<input class="submit" name="submit" type="submit" value="Delete School '.$name.'"/>';
      echo '</div>';
      echo '<div class="returnButton"><a href="index.php#'.schoolAnchor(strhtml($schoolID)).'">Return without deleting</a></div>';
   }
   endContent();
}
?>
