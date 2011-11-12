<?php
set_include_path('../include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/dbCommand.inc");
require_once("toolkit/redirect.inc");
require_once("form/schoolForm.inc");
require_once("model/data.inc");
require_once("model/school.inc");
//require_once("redirect.inc");

$wasUpdated = FALSE;
$readRecord = TRUE;
$corrMsg = '';
$db_conn = false;
$fail = dbConnect($db_conn);
$school = new School;
if ($fail != '')
{
   notifyError($fail, "editSchool.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
   $readRecord = FALSE;
}
else if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   // debugArr('post', $_POST);
   // begin form processing
   $corrMsg = $school->validatePost($_POST);
   if ($corrMsg == '')
   {
      $fail = $school->createOrUpdateRecord($db_conn);
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "editSchool.php");
         $corrMsg = "<it>Internal: failed data update.</it>";
      }
   }
}
if ($readRecord)
{
   // not POST
   $id = $_GET['id'];
   if ($id != '')
   {
      // is edit for school with given id
      //      debug ('editing school id '.$id);
      $fail = $school->readRecord($db_conn, $id);
      if ($fail != '')
      {
         notifyError($fail, "editSchool.php");
         $corrMsg ="<li>Internal: failed access to school record of ".$id."</li>";
      }
   }
}
dbClose($db_conn);
// Redirect logic
if ($wasUpdated)
{
   $nextURL = "index.php#".schoolAnchor($school->id);
   getNextPage($nextURL);
}
else
{
   startHead("Flight School Information");
   startContent();
   if ($corrMsg != '')
   {
      echo '<ul class="error">'.$corrMsg.'</ul>';
   }
   echo '<form class="recordForm" action="editSchool.php" method="post">';
   schoolForm($school);
   echo '<input name="id" type="hidden" value="'.inthtml($school->id).'"/>';
   echo '<div class="submit">';
   echo '<input class="submit" name="submit" type="submit" value="Save Changes"/>';
   echo '</div>';
   echo '</form>';
   echo '<div class="returnButton"><a href="index.php">Return without saving</a></div>';
   endContent();
}
?>
