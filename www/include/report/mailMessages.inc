<?php
require_once('config.inc');
require_once('toolkit/useful.inc');
require_once('model/school.inc');
require_once('model/instructor.inc');

function automatedMessage()
{
   return "\nThis is an automated message from the IAC aerobatic schools listing service.\n";
}

function mailInstructorUpdate($changeType, $school, $instructor)
{
   global $admin_email, $schools_email;
   $subject = "IAC school listing instructor $changeType request";
   $mailContent = $subject."\n";
   $mailContent .= $school->printRef();
   $mailContent .= $changeType.' '.$instructor->printData();
   $mailContent .= automatedMessage();
   $headers = "From: " . $admin_email . "\r\n";
   $headers .= "CC: " . $school->email . "\r\n";
   do_email($schools_email, $subject, $mailContent, $headers);
}

function mailSchoolUpdate($changeType, $school)
{
   global $admin_email, $schools_email;
   $subject = "IAC school listing $changeType request";
   $mailContent = $subject."\n";
   $mailContent .= $changeType . ' ' . $school->printData();
   $mailContent .= automatedMessage();
   $headers = "From: " . $admin_email . "\r\n";
   $headers .= "CC: " . $school->email . "\r\n";
   do_email($schools_email, $subject, $mailContent, $headers);
}
?>