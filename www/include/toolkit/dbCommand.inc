<?php
require_once('config.inc');
require_once('toolkit/useful.inc');

/**
Connect to the database.
Requires database connection handle passed by reference.
Returns failure HTML content, empty if successful.
*/
function dbConnect(&$db_conn)
{
   global $dbprefix, $dbuser, $dbpasswd;
   return dbConnectl($dbprefix.$dbuser, $dbpasswd, $db_conn);
}

function dbConnectl($dbuser, $dbpasswd, &$db_conn)
{
   global $dbhost, $dbprefix, $dbname;
   $fail = '';
   $db_conn = mysql_connect($dbhost, $dbuser, $dbpasswd);
   if (!$db_conn) 
   {
      $fail = notifyError("Failed database connection", $dbuser."@".$dbhost);
   }
   else
   {
      $dbsel = $dbprefix.$dbname;
      if (!mysql_select_db($dbsel))
      {
         $fail = notifyError("Failed database selection", $dbhost."/".$dbsel);
      }
   }
   return $fail;
}

function dbExec($db_conn, $query)
{
   $fail = '';
   mysql_query($query,$db_conn);
   if (mysql_errno() != 0)
   {
      $fail = notifyError(mysql_error(), $query);
   }
   return $fail;
}

function dbQuery($db_conn, $query)
{
   $result = mysql_query($query, $db_conn);
   if (mysql_errno() != 0)
   {
      notifyError(mysql_error(), $query);
      $result = false;
   }
   return $result;
}

function dbErrorNumber()
{
   return mysql_errno();
}

function dbErrorText()
{
   return mysql_error();
}

function dbCountResult($result)
{
   return mysql_num_rows($result);
}

function dbLastID()
{
   return mysql_insert_id();
}

function dbFetchAssoc($result)
{
   return mysql_fetch_assoc($result);
}

function dbFetchRow($result)
{
   return mysql_fetch_row($result);
}

function dbBegin($db_conn)
{
   return dbExec($db_conn, "start transaction");
}

function dbCommit($db_conn)
{
   return dbExec($db_conn, "commit");
}

function dbRollback($db_conn)
{
   return dbExec($db_conn, "rollback");
}

function dbClose($db_conn)
{
   if ($db_conn) mysql_close($db_conn);
}

/*
   Copyright 2008 International Aerobatic Club, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
?>
