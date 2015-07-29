<?php
// requires globally defined:  $debug, $email_action, $admin_email
require_once('config.inc');
require_once('toolkit/encodeHTML.inc');

/**
 Generate an eight character string with random upper and lower-case
 Latin alphabetic characters or Arabic numerals.
 */
function generatePassword()
{
   $pwd = "";
   for($i = 1; $i <= 8; ++$i)
   {
      $c[0] = chr(rand(65, 90));
      $c[1] = chr(rand(97,122));
      $c[2] = chr(rand(48, 57));
      $idx = rand(0, 2);
      $pwd .= $c[$idx];
   }
   return $pwd;
}

function isDebug()
{
   global $debug;
   return isset($debug) && $debug;
}

/**
 Display each element of an array, one line per element.
 */
function debugArr($message, $arr)
{
   global $debug;
   debug($message);
   if (isDebug())
   {
      if (is_array($arr)) foreach ($arr as $key => $value)
      {
         debug($key.':'.$value.':', false);
      }
      else
      {
         debug('non array value is '.$arr, false);
      }
   }
}

/**
 Check debug, do debug_action if defined
 */
function debug($message, $doTimestamp=true)
{
   global $debug, $debug_action, $admin_email;
   if (isDebug())
   {
      if (isSet($debug_action)) $action = $debug_action; else $action="echo";
      if ($action == "echo")
      {
         echo "<p>".$message."</p>\n";
      }
      else if (action == "mail")
      {
         $fromAddress = "From: ".$admin_email."\r\n";
         mail($admin_email, "debug output", $message, $fromAddress);
      }
      else
      {
         $log = fopen($debug_action, 'a');
         if (!$log) echo ('dobug failed to open file "'.$debug_action.'"');
         else {
            if ($doTimestamp) fwrite($log, date('Y-m-d:H:i:s')."\n");
            fwrite($log, $message."\n");
            fclose($log);
         }
      }
   }
}

/**
 Check email_action, send mail if not, otherwise echo mail.
 email: comma separated list of recipient addresses
 subject: appears as the email subject
 mailContest: appears as the email contest
 headers: email headers terminated with \r\n must include From: header.
 */
function do_email($email, $subject, $mailContent, $headers)
{
   global $email_action;
   if (isSet($email_action)) $action = $email_action; else $action="mail";
   if ($action == "echo")
   {
      echo "<p>Mail<ul>\n";
      echo "<li>Mail to:".$email."</li>\n";
      echo "<li>Subject:".$subject."</li>\n";
      echo "<li>Content:".$mailContent."</li>\n";
      echo "<li>Headers:".$headers."</li>\n";
      echo "</ul></p>\n";
   }
   else if ($action == "mail")
   {
      mail($email, $subject, $mailContent, $headers);
   }
   else
   {
      $log = fopen($email_action, 'a');
      if (!$log) echo ('email failed to open file "'.$email_action.'"');
      else {
         fwrite($log, date('Y-m-d:H:i:s')."\n");
         fwrite($log, "Mail to:".$email."\n");
         fwrite($log, "Subject:".$subject."\n");
         fwrite($log, "Content:".$mailContent."\n");
         fwrite($log, "Headers:".$headers."\n");
         fclose($log);
      }
   }
}

/**
 Handle bad errors. Log them or mail them to the administrator.
 message gets repeated in the HTML error content.
 message and place get repeated in the administrator message.
 Return HTML content about the error.
 */
function notifyError($message, $context)
{
   global $admin_email;
   $subject = "script error";
   $mailContent = "Script error in ".$context." is ".$message.".\n";
   if (isset($_SESSION["userID"]))
   {
      $mailContent .= "Encountered by registrant ".$_SESSION["userID"];
   }
   $fromAddress = "From: ".$admin_email."\r\n";
   do_email($admin_email, $subject, $mailContent, $fromAddress);
   return "Internal error:".
   strhtml($message).". Mail sent to adminstrator.";
}

/**
 Validate an email address.
 Provide email address (clean input)
 Returns true if the email address has the email address format
 and the domain exists.
 */
function validEmail($email)
{
   global $debug;
   $isValid = true;
   $atIndex = strrpos($email, "@");
   if (is_bool($atIndex) && !$atIndex)
   {
      $isValid = false;
   }
   else
   {
      $domain = substr($email, $atIndex+1);
      $local = substr($email, 0, $atIndex);
      $localLen = strlen($local);
      $domainLen = strlen($domain);
      if ($localLen < 1 || $localLen > 64)
      {
         // local part length exceeded
         $isValid = false;
      }
      else if ($domainLen < 1 || $domainLen > 255)
      {
         // domain part length exceeded
         $isValid = false;
      }
      else if ($local[0] == '.' || $local[$localLen-1] == '.')
      {
         // local part starts or ends with '.'
         $isValid = false;
      }
      else if (preg_match('/\\.\\./', $local))
      {
         // local part has two consecutive dots
         $isValid = false;
      }
      else if (!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain))
      {
         // character not valid in domain part
         $isValid = false;
      }
      else if (preg_match('/\\.\\./', $domain))
      {
         // domain part has two consecutive dots
         $isValid = false;
      }
      else if (!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local)))
      {
         // character not valid in local part unless local part is quoted
         if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local)))
         {
            $isValid = false;
         }
      }
      if ($isValid && !(isset($debug) || checkdnsrr($domain,"MX") || checkdnsrr($domain, "A")))
      {
         // domain not found in DNS
         $isValid = false;
      }
   }
   return $isValid;
}
?>
<?php
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
