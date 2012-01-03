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
   header('Content-Type:text/tab-separated-values;charset=utf-8');
   header('Content-Disposition: attachment;filename="IAC_SchoolsMailmerge.tsv"');
   exportSchoolList($dbResult);
}
dbClose($db_conn);

function querySchoolRecords($db_conn)
{
   $query = "select name, contact, addressLine1, addressLine2, ".
   "city, state, zip, country, phone, email from school";
   $query .= ' order by country, state, name';
   return dbQuery($db_conn, $query);
}

function exportSchoolList($dbResult)
{
   $isFirst = true;
   $rcd = dbFetchAssoc($dbResult);
   while ($rcd)
   {
      //      debugArr('schoolList record',$rcd);
      if ($isFirst)
      {
         $ctCol = 0;
         foreach ($rcd as $key => $value)
         {
            if ($ctCol > 0)
            {
               echo "\t";
            }
            echo $key;
            ++$ctCol;
         }
         echo "\n";
         $isFirst = false;
      }
      $ctCol = 0;
      foreach ($rcd as $key => $value)
      {
         if ($ctCol > 0)
         {
            echo "\t";
         }
         echo $value;
         ++$ctCol;
      }
      echo "\n";
      $rcd = dbFetchAssoc($dbResult);
   }
}
?>
