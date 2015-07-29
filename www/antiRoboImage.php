<?php
/*  antiRoboImage.php, acrs/admin, dlco, 10/23/2010
 *  display Captcha image
 *
 *  Changes:
 *    10/23/2010 jim_ward       be sensitive to presence of FreeType support; if absent, imagettftext() doesn't exist
 *                              so use GDF font & functions instead.
 */

session_start();
set_include_path('./include');
require("config.inc");
require('toolkit/useful.inc');
require("secureimage.inc");

$gd_info = gd_info();
$img = new securimage();

/*  If no FreeType support is available, don't call the undefined imagettftext() function from securimage::show().
 */
if (! $gd_info["FreeType Support"])
   $img->use_gd_font = true ;

$img->show("antiRoboImage.jpg");
debug("antiRobotCheat: " . $img->code);
?>
