<?php
require_once('toolkit/useful.inc');
require_once('toolkit/encodeHTML.inc');
require_once('toolkit/dbCommand.inc');
require_once('model/data.inc');

function doStatesList($db_conn, $filter = '')
{
   $corrMsg = '';
   $dbResult = queryStates($db_conn, $filter);
   if ($dbResult == FALSE)
   {
      notifyError('Failed query states '.dbErrorText(), 'statesList.inc');
      $corrMsg = "<li>Internal: failed query states</li>";
   }
   if ($corrMsg == '')
   {
      formatStatesList($dbResult);
   }
   return $corrMsg;
}

function queryStates($db_conn, $filter = '')
{
   // TODO is there an SQL way to get unique country, state combinations?
   $query = "select country, airstate from school";
   if ($filter != '')
   {
      $query .= ' where '. $filter;
   }
   $query .= ' order by country, airstate';
   //debug('statesList->queryStates query is '.$query);
   return dbQuery($db_conn, $query);
}

function formatStatesList($dbResult)
{
   echo '<div class="states">';
   $rcd = dbFetchRow($dbResult);
   $lastTag = '';
   while ($rcd)
   {
      //debugArr('stateList->formatStatesList record',$rcd);
      $country = strhtml($rcd[0],32);
      $state = strhtml($rcd[1],32);
      $tag = stateAnchor($state, $country);
      if ($tag != $lastTag){
         echo '<a href="#'.$tag.'">'.displayLoc('', $state, $country);
         echo "</a>\n";
         $lastTag = $tag;
      }
      $rcd = dbFetchRow($dbResult);
   }
   echo "</div>";
}

?>