<?php
set_include_path('../include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/dbCommand.inc");
require_once("toolkit/redirect.inc");
require_once("form/instructorForm.inc");
require_once("report/schoolList.inc");
require_once("model/school.inc");
require_once("model/instructor.inc");
require_once("model/data.inc");
//require_once("redirect.inc");

$wasUpdated = FALSE;
$readRecord = TRUE;
$corrMsg = '';
$db_conn = false;
$fail = dbConnect($db_conn);
$instructor = new Instructor;
$school = new School;
if ($fail != '')
{
   notifyError($fail, "editInstructor.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
   $readRecord = FALSE;
}
else if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   //   debugArr('instructor post', $_POST);
   // begin form processing
   $corrMsg = $instructor->validatePost($_POST);
   if ($corrMsg == '')
   {
      $fail = $instructor->createOrUpdateRecord($db_conn);
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "editInstructor.php");
         $corrMsg = "<it>Internal: failed data update.</it>";
      }
   }
}
if ($readRecord)
{
   // not POST
   $id = $_GET['id'];
   //   debug('editInstructor id is '.$id);
   if (isSet($id))
   {
      // is edit for instructor with given id
      //      debug ('editing instructor id '.$id);
      $fail = $instructor->readRecord($db_conn, $id);
      if ($fail != '')
      {
         notifyError($fail, "editInstructor.php");
         $corrMsg ="<li>Internal: failed access to instructor record of ".$id."</li>";
      }
   }
   else
   {
      $instructor->schoolID = $_GET['schoolID'];
      //      debug('editInstructor school is '.$instructor->schoolID);
      if (!isSet($instructor->schoolID))
      {
         $corrMsg = "<li>Please navigate from the school editing form.</li>";
      }
   }
   if ($corrMsg == '')
   {
      $school->readRecord($db_conn, $instructor->schoolID);
   }
}
dbClose($db_conn);
// Redirect logic
if ($wasUpdated)
{
   $nextURL = "index.php#".instructorAnchor($instructor->id);
   getNextPage($nextURL);
}
else
{
   startHead("Instructor Information");
   startContent();
   if ($corrMsg != '')
   {
      echo '<ul class="error">'.$corrMsg.'</ul>';
   }
   echo '<div class="instSchoolName">'.$school->name.'</div>';
   echo '<form class="recordForm" action="editInstructor.php" method="post">';
   instructorForm($instructor);
   echo '<div class="submit">';
   echo '<input class="submit" name="submit" type="submit" value="Save Changes"/>';
   echo '</div>';
   echo '<div class="returnButton"><a href="index.php#'.instructorAnchor($instructor->id).'">Return without saving</a></div>';
   endContent();
}
?>
