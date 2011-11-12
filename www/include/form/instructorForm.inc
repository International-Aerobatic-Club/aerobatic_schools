<?php
function instructorForm($instructor)
{
echo "<table>\n";
echo "	<tbody>\n";
echo "		<tr>\n";
echo "			<td class=\"form_text\"><label for=\"in_givenName\">First name:";
echo "			</label><input id=\"in_givenName\" name=\"givenName\" \" maxlength=\"32\"\n";
echo "				size=\"24\" value=\"".strhtml($instructor->givenName)."\"/></td>\n";
echo "			<td class=\"form_text\"><label for=\"in_sirName\">Last name:";
echo "			</label><input id=\"in_sirName\" name=\"sirName\" \" maxlength=\"32\"\n";
echo "				size=\"24\" value=\"".strhtml($instructor->sirName)."\"/></td>\n";
echo "		</tr>\n";
echo "		<tr>\n";
echo "			<td class=\"form_check\"><label for=\"in_ratings\">Instructor Designations/Abbreviations\n";
echo "			(check all that apply):</label>\n";
echo "			<fieldset id=\"in_ratings\"><ul>\n";
echo "			<li><div class='check_item'><input class=\"form_check\"\n";
echo "				type=\"checkbox\" id=\"in_ratings_CFI\" name=\"ratings_CFI\" ".strChecked($instructor->isCFI())."/><label\n";
echo "				for='in_ratings_CFI'>FAA Certified Flight Instructor (CFI)</label></div>\n";
echo "			</li><li><div class='check_item'><input class=\"form_check\"\n";
echo "				type=\"checkbox\" id=\"in_ratings_FIA\" name=\"ratings_FIA\" ".strChecked($instructor->isFIA())."/><label\n";
echo "				for='in_ratings_FIA'>Aerobatic Instructor (CFI-A or FI-A)</label></div>\n";
echo "			</li><li><div class='check_item'><input class=\"form_check\"\n";
echo "				type=\"checkbox\" id=\"in_ratings_MCFI\" name=\"ratings_MCFI\" ".strChecked($instructor->isMCFI())."/><label\n";
echo "				for='in_ratings_MCFI'>Master CFI (MCFI or MCFI-A)</label></div>\n";
echo "			</li><li><div class='check_item'><input class=\"form_check\"\n";
echo "				type=\"checkbox\" id=\"in_ratings_ACE\" name=\"ratings_ACE\" ".strChecked($instructor->isACE)."/><label\n";
echo "				for='in_ratings_ACE'>ICAS Aerobatic Competency Evaluator\n";
echo "			(A.C.E.)</label></div>\n";
echo "			</li></ul></fieldset>\n";
echo "			</td>\n";
echo "		</tr>\n";
echo "	</tbody>\n";
echo "</table>\n";
echo "<input type='hidden' name='id' value='".intSQL($instructor->id)."'/>";
echo "<input type='hidden' name='schoolID' value='".intSQL($instructor->schoolID)."'/>";
}
?>
