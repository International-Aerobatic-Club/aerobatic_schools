<?php
set_include_path('include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("form/change.inc");
require_once("form/schoolForm.inc");
require_once("model/school.inc");
require_once("model/instructor.inc");
require_once("model/data.inc");
require_once("report/mailMessages.inc");
require_once("secureimage.inc");

$wasUpdated = FALSE;
$corrMsg = '';
$school = new School;
$fail = '';
if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   //   debugArr('school post', $_POST);
   // begin form processing
   $corrMsg = $school->validatePost($_POST);
   $antirobo = new securimage();
   if (!$antirobo->check($_POST['antiRobot']))
   {
      $corrMsg .= "<li>Copy the anti-robot image text.</li>";
   }
   $changeType = $_POST['change'];
   if ($corrMsg == '')
   {
      $fail = mailSchoolUpdate($changeType, $school);
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "schoolUpdate.php");
         $corrMsg = "<it>Internal: failed email update.</it>";
      }
   }
}
else
{
   $_POST['change'] = 'update';
}
startHead("School Information");
startContent();
echo "<h1>School Update</h1>";
if ($corrMsg != '')
{
   echo '<ul class="error">'.$corrMsg.'</ul>';
}
if ($wasUpdated)
{
   ?>
<p class="confirmation">Thank you. You have mailed your school update to
your IAC liason who will review and post your changes. You will receive
a copy of the email.</p>
   <?php
   echo '<div class="returnButton"><a href="resources.php">Return to the resources page.</a>.</div>';
}
else {
   echo '<form class="recordForm" action="schoolUpdate.php" method="post">';
   changeTypeFormEntry($_POST);
   schoolForm($school);
   echo '<div class="antiRobo">';
   echo '<p>Copy the anti-robot image text:</p>';
   echo '<img src="antiRoboImage.php?sid=' .
     md5(uniqid(time())) . '" alt="anti-robot image"/>';
   echo '<input class="antiRobot" type="text" size="8" maxlength="8" name="antiRobot"/>';
   echo '</div>';
   echo '<div class="submit">';
   echo '<input class="submit" name="submit" type="submit" value="Mail Updates"/>';
   echo '</div>';
   echo '<div class="returnButton"><a href="resources.php">Return without sending changes</a>.</div>';
}
endContent();
?>
