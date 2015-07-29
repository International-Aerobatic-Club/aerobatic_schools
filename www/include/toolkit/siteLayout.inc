<?php
require_once('config.inc');
function startHead($title)
{
   global $baseURL;
   ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta name="generator"
	content="HTML Tidy for Linux (vers 6 November 2007), see www.w3.org"/>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<meta name="rating" content="General"/>
<meta name="revisit-after" content="7 days"/>
<meta name="ROBOTS" content="ALL"/>
<meta http-equiv="Content-Style-Type" content="text/css"/>
   <?php
   echo '<link href="'.$baseURL.'style/site.css" type="text/css" rel="stylesheet" />';
   echo "<title>" . $title . "</title>";
}

function startContent($title='Aerobatic Flight Schools', $bodyAttributes = '')
{
   ?>
<style type="text/css">
div.c4 {
	position: absolute;
	top: 73px;
	left: 160px;
	z-index: 2;
	color: white;
	vertical-align: bottom;
	font-family: Times, serif;
	font-size: 36pt;
}

div.c3 {
	position: absolute;
	top: 75px;
	left: 162px;
	z-index: 1;
	color: black;
	vertical-align: bottom;
	font-family: Times, serif;
	font-size: 36pt;
}

div.c2 {
	z-index: 1;
	position: relative;
	top: 0px;
	left: 0px
}

div.c1 {
	z-index: 0;
	position: absolute;
	left: 0px;
	top: 0px;
}
</style>
   <?php
   global $baseURL;
   echo "</head><body " . $bodyAttributes . ">";
   echo '<div class="c1"><img src="'.$baseURL.'images/schoolBanner5.png" alt="Grass airstrip in summer, with biplane wing and hangar building. NY1 recto verso"/></div>';
   echo '<div class="c2"><img src="'.$baseURL.'images/BannerIAC.png" alt="IAC logo"/></div>';
   echo '<div class="c3">'.$title.'</div>';
   echo '<div class="c4">'.$title.'</div>';
   echo '<div class="content">';
}

function endContent()
{
   global $baseURL;
   echo '</div><div class="footer"><p>';
   echo 'Copyright &copy;2009-2013 International Aerobatic Club. All logos, ';
   echo 'trademarks, pictures, and videos are the property of their respective ';
   echo 'owners. Contact ';
   echo '<a href="mailto:doug@wbreeze.com" class="footer">Douglas Lovell</a> ';
   echo 'with comments or questions about the display or content of this web ';
   echo 'page. Refer to ';
   echo '<a href="'.$baseURL.'resources.php">school resources</a> ';
   echo 'for comments, questions, or information about school listings.</p>';
   echo '</div>';
   echo "</body></html>\n";
}
?>
