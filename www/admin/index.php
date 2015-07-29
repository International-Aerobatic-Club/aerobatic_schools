<?php
set_include_path('../include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/dbCommand.inc");
require_once("report/schoolList.inc");
require_once("report/statesList.inc");

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
if ($corrMsg != '')
{
   echo '<ul class="error">'.$corrMsg.'</ul>';
}
else
{
   echo '<a name="top"/>';
   $corrMsg = doStatesList($db_conn);
   echo "<div class='command'><a href='../index.php'>view public listing</a></div>";
   echo "<div class='command'><a href='mailList.php'>download mail merge addresses</a></div>";
   echo "<div class='command'><a href='emailList.php'>download email address list</a></div>";
   echo "<div class='command'><a href='editSchool.php'>add a school</a></div>";
   $corrMsg .= doSchoolList($db_conn, '', TRUE);
}
if ($corrMsg != '')
{
   echo '<ul class="error">'.$corrMsg.'</ul>';
}
endContent();
dbClose($db_conn);
?>
