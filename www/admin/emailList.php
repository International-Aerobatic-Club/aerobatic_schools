<?php
set_include_path('../include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once("toolkit/dbCommand.inc");

$corrMsg = '';
$db_conn = false;
$dbResult = false;
$fail = dbConnect($db_conn);
if ($fail != '')
{
   notifyError($fail, "index.php");
   $corrMsg = "<li>Internal: failed access to schools database</li>";
}
else
{
   $dbResult = querySchoolRecords($db_conn);
   if ($dbResult == FALSE)
   {
      notifyError('Failed query schools '.dbErrorText(), 'index.php');
      $corrMsg = "<li>Internal: failed query schools</li>";
   }
}
if ($corrMsg != '')
{
   startHead("Aerobatic Flight Schools");
   startContent();
   echo '<ul class="error">'.$corrMsg.'</ul>';
   endContent();
}
else
{
   header('Content-Type: text/plain;charset=utf-8');
   header('Content-Disposition: attachment;filename="IAC_SchoolsEmail.txt"');
   exportMailList($dbResult);
}
dbClose($db_conn);

function querySchoolRecords($db_conn)
{
   $query = "select distinct name, email from school";
   $query .= ' order by name';
   return dbQuery($db_conn, $query);
}

function exportMailList($dbResult)
{
   $rcd = dbFetchAssoc($dbResult);
   while ($rcd)
   {
      //      debugArr('schoolList record',$rcd);
      echo $rcd['name'].' <'.$rcd['email'].">,\n";
      $rcd = dbFetchAssoc($dbResult);
   }
}
?>
