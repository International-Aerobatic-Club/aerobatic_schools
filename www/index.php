<?php
set_include_path('include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/encodeSQL.inc");
require_once("toolkit/dbCommand.inc");
require_once("model/school.inc");
require_once("report/schoolList.inc");
require_once("report/statesList.inc");
require_once("report/listingMessages.inc");

$corrMsg = '';
$db_conn = false;
$dbResult = false;
$fail = dbConnect($db_conn);
if ($fail != '')
{
   notifyError($fail, "index.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
}
startHead("Aerobatic Flight Schools");
startContent();
echo '<a name="top"/>';
echo '<p><a href="resources.php">Resources for Aerobatic Instructors and Students</a></p>';
if ($corrMsg == '')
{
   $where = '';
   $course = $_GET['course'];
   if (!empty($course))
   {
      $where = encodeWhereSet('course', $course);
   }
   $state = $_GET['state'];
   if (!empty($state))
   {
      $state = encodeWhereIn('airState', $state);
      if (!empty($where))
      {
         $where .= ' and ' . $state;
      }
      else
      {
         $where = $state;
      }
   }
   $corrMsg = doStatesList($db_conn, $where);
   disclaimer();
   listingInstructions();
   $corrMsg .= doSchoolList($db_conn, $where);
}
if ($corrMsg != '')
{
   echo '<ul class="error">'.$corrMsg.'</ul>';
}
endContent();
dbClose($db_conn);
?>
