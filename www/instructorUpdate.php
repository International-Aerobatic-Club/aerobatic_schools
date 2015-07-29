<?php
set_include_path('include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("form/change.inc");
require_once("form/instructorForm.inc");
require_once("model/school.inc");
require_once("model/instructor.inc");
require_once("model/data.inc");
require_once("report/mailMessages.inc");
require_once('secureimage.inc');

function schoolRefForm($school)
{
   echo "<table><tbody>\n";
   echo "<td class=\"form_text\" colspan=\"2\"><label for=\"in_name\">Name of school:</label><input id=\"in_name\" name=\"name\" value=\"".strhtml($school->name)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\"><label for=\"in_city\">Airport City:</label><input id=\"in_city\" name=\"airCity\" value=\"".strhtml($school->airCity)."\" maxlength=\"32\" size=\"24\"/></td>\n";
   echo "<td class=\"form_text\"><label for=\"in_state\">Airport State or Province (USA use two letter ID):</label><input id=\"in_state\" name=\"airState\" value=\"".strhtml($school->airState)."\" maxlength=\"32\" size=\"24\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"2\"><label for=\"in_contact\">Contact name:</label><input id=\"in_contact\" name=\"contact\" value=\"".strhtml($school->contact)."\" maxlength=\"64\" size=\"40\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\"><label for=\"in_phone\">Phone:</label><input id=\"in_phone\" name=\"phone\" value=\"".strhtml($school->phone)."\" maxlength=\"16\" size=\"14\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"2\"><label for=\"in_email\">Email:</label><input id=\"in_email\" name=\"email\" value=\"".strhtml($school->email)."\" maxlength=\"256\" size=\"40\"/></td>\n";
   echo "</tr><tr>\n";
   echo "</tbody></table>\n";
}

$wasUpdated = FALSE;
$corrMsg = '';
$instructor = new Instructor;
$school = new School;
$fail = '';
if (isset($_POST["submit"]))
{
   $readRecord = FALSE;
   //   debugArr('instructor post', $_POST);
   // begin form processing
   $corrMsg = $school->validatePost($_POST, true);
   $corrMsg .= $instructor->validatePost($_POST);
   $antirobo = new securimage();
   if (!$antirobo->check($_POST['antiRobot']))
   {
      $corrMsg .= "<li>Copy the anti-robot image text.</li>";
   }
   $changeType = $_POST['change'];
   if ($corrMsg == '')
   {
      $fail = mailInstructorUpdate($changeType, $school, $instructor);
      if ($fail == '')
      {
         $wasUpdated = TRUE;
      }
      else
      {
         notifyError($fail, "school.php");
         $corrMsg = "<it>Internal: failed email update.</it>";
      }
   }
}
else
{
   $_POST['change'] = 'update';
}
startHead("Instructor Information");
startContent();
echo "<h1>Instructor Update</h1>";
if ($corrMsg != '')
{
   echo '<ul class="error">'.$corrMsg.'</ul>';
}
if ($wasUpdated)
{
   ?>
<p class="confirmation">Thank you. You have mailed your instructor
update to your IAC liason who will review and post your changes. You
will receive a copy of the email.</p>
<p class="confirmation">Submit this form again for changes to other
instructors.</p>
   <?php
}
echo '<form class="recordForm" action="instructorUpdate.php" method="post">';
changeTypeFormEntry($_POST);
echo "<h3>School Reference:</h3>\n";
schoolRefForm($school);
echo "<h3>Instructor information:</h3>\n";
instructorForm($instructor);
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
endContent();
?>
