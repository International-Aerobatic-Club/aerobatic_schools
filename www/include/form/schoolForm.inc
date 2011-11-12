<?php
require_once('toolkit/encodePOST.inc');
require_once('toolkit/encodeHTML.inc');

function schoolForm($school)
{
   ?>
<!--
   echo "<table><tbody>\n";
   echo "<tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_name\">Name of school:</label><input id=\"in_name\" name=\"name\" value=\"".strhtml($school->name)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_addressLine1\">Address (line 1):</label><input id=\"in_addressLine1\" name=\"addressLine1\" value=\"".strhtml($school->addressLine1)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_addressLine2\">Address (line 2):</label><input id=\"in_addressLine2\" name=\"addressLine2\" value=\"".strhtml($school->addressLine2)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\"><label for=\"in_city\">City (or city and country):</label><input id=\"in_city\" name=\"city\" value=\"".strhtml($school->city)."\" maxlength=\"32\" size=\"24\"/></td>\n";
   echo "<td class=\"form_text\"><label for=\"in_state\">State (international leave blank):</label><input id=\"in_state\" name=\"state\" value=\"".strhtml($school->state)."\" maxlength=\"2\" size=\"2\"/></td>\n";
   echo "<td class=\"form_text\"><label for=\"in_zip\">Postal Code:</label><input id=\"in_zip\" name=\"zip\" value=\"".strhtml($school->zip)."\" maxlength=\"16\" size=\"10\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_contact\">Contact name:</label><input id=\"in_contact\" name=\"contact\" value=\"".strhtml($school->contact)."\" maxlength=\"64\" size=\"40\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\"><label for=\"in_phone\">Phone:</label><input id=\"in_phone\" name=\"phone\" value=\"".strhtml($school->phone)."\" maxlength=\"16\" size=\"14\"/></td>\n";
   echo "<td class=\"form_text\"><label for=\"in_fax\">Fax:</label><input id=\"in_fax\" name=\"fax\" value=\"".strhtml($school->fax)."\" maxlength=\"16\" size=\"14\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_email\">Email:</label><input id=\"in_email\" name=\"email\" value=\"".strhtml($school->email)."\" maxlength=\"256\" size=\"40\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_web\">Web site:</label><input id=\"in_web\" name=\"web\" value=\"".strhtml($school->web)."\" maxlength=\"256\" size=\"40\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_aircraft\">Aircraft:</label><input id=\"in_aircraft\" name=\"aircraft\" value=\"".strhtml($school->aircraft)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   echo "<td class=\"form_text\" colspan=\"3\"><label for=\"in_notes\">Notes:</label><input id=\"in_notes\" name=\"notes\" value=\"".strhtml($school->notes)."\" maxlength=\"256\" size=\"80\"/></td>\n";
   echo "</tr><tr>\n";
   $courses = array();
   sqlSetValueToPostData($school->courses, 'course', $courses);
   echo "<td class=\"form_check\" colspan=\"2\">\n";
   echo "<label for=\"in_course\">Courses:</label><fieldset id=\"in_course\" legend=\"Courses\">\n";
   foreach (School::$courseValues as $crs)
   {
      echo "<div class='check_item'><input class=\"form_check\" type=\"checkbox\" id=\"in_course_".$crs."\" name=\"course_".$crs."\" ".isChecked($courses,'course',$crs).">".School::$courseDescriptions[$crs]."</input></div>\n";
   }
   echo "</fieldset></td>\n";
   echo "</tr>\n";
   echo "</tbody></table>\n";
   echo "<input id='in_id' type='hidden' name='id', value='".$school->id."'/>";
    -->
<table>
	<tbody>
		<tr>
			<td colspan="3" class="form_text"><label for="in_name">Name of
			school:</label><input id="in_name" name="name"
			<?php echo "value=\"". strhtml($school->name)."\""?> maxlength="256"
				size="80" /></td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_contact">Contact
			name:</label><input id="in_contact" name="contact"
			<?php echo "value=\"". strhtml($school->contact)."\""?>
				maxlength="64" size="40" /></td>
		</tr>
		<tr>
			<td class="form_text"><label for="in_phone">Phone:</label><input
				id="in_phone" name="phone"
				<?php echo "value=\"". strhtml($school->phone)."\""?> maxlength="16"
				size="14" /></td>
			<td class="form_text"><label for="in_fax">Fax:</label><input
				id="in_fax" name="fax"
				<?php echo "value=\"". strhtml($school->fax)."\""?> maxlength="16"
				size="14" /></td>
		</tr>
		<tr>
			<td colspan="3">Provide the country, primary airport, city, and state
			or province where you base operations. If you serve additional nearby
			airports, list airport identifiers in the notes. Submit a separate
			listing if you have a base at another, significantly distant airport.</td>
		</tr>
		<tr>
			<td class="form_text"><label for="in_airport">Base Airport ID (USA use FAA three letter ID):</label>
			<input id="in_airport" name="airport"
			<?php echo "value=\"". strhtml($school->airport)."\""?>
				maxlength="4" size="4" /></td>
			<td class="form_text"><label for="in_country">Country (leave empty
			for USA):</label><input id="in_country" name="country"
			<?php echo "value=\"". strhtml($school->country)."\""?>
				maxlength="32" size="24" /></td>
		</tr>
		<tr>
			<td class="form_text"><label for="in_airCity">Airport City:</label><input
				id="in_airCity" name="airCity"
				<?php echo "value=\"". strhtml($school->airCity)."\""?>
				maxlength="32" size="24" /></td>
			<td class="form_text"><label for="in_airState">Airport State or
			Province (USA use two letter ID):</label> <input id="in_airState"
				name="airState"
				<?php echo "value=\"". strhtml($school->airState)."\""?>
				maxlength="32" size="24" /></td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_email">Email:</label><input
				id="in_email" name="email"
				<?php echo "value=\"". strhtml($school->email)."\""?>
				maxlength="256set" size="40" /></td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_web">Web site:</label><input
				id="in_web" name="web"
				<?php echo "value=\"". strhtml($school->web)."\""?> maxlength="256"
				size="40" /></td>
		</tr>
		<tr>
			<td colspan="3">List makes and models of aerobatic aircraft available
			for instruction or rental.</td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_aircraft">Aircraft:</label><input
				id="in_aircraft" name="aircraft"
				<?php echo "value=\"". strhtml($school->aircraft)."\""?>
				maxlength="256" size="80" /></td>
		</tr>
		<tr>
			<td colspan="3" class="form_check"><label for="in_course">Courses:</label>
			<fieldset id="in_course">
			<?php    $courses = array();
			sqlSetValueToPostData($school->courses, 'course', $courses);
			foreach (School::$courseValues as $crs)
			{
			   echo "<div class='check_item'><input class=\"form_check\" type=\"checkbox\" id=\"in_course_".$crs."\" name=\"course_".$crs."\" ".isChecked($courses,'course',$crs).">".School::$courseDescriptions[$crs]."</input></div>\n";
			}?></fieldset>
			</td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_notes">Notes:</label><input
				id="in_notes" name="notes"
				<?php echo "value=\"". strhtml($school->notes)."\""?>
				maxlength="256" size="80" /></td>
		</tr>
		<tr>
			<td colspan="3">The following mailing address information is for IAC
			contact purposes only. Your listing will not display it.</td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_addressLine1">Address:</label><input
				id="in_addressLine1" name="addressLine1"
				<?php echo "value=\"". strhtml($school->addressLine1)."\""?>
				maxlength="256" size="80" /></td>
		</tr>
		<tr>
			<td colspan="3" class="form_text"><label for="in_addressLine2">Address:</label><input
				id="in_addressLine2" name="addressLine2"
				<?php echo "value=\"". strhtml($school->addressLine2)."\""?>
				maxlength="256" size="80" /></td>
		</tr>
		<tr>
			<td class="form_text"><label for="in_city">City:</label><input
				id="in_city" name="city"
				<?php echo "value=\"". strhtml($school->city)."\""?> maxlength="32"
				size="24" /></td>
			<td class="form_text"><label for="in_state">State or Province:</label><input
				id="in_state" name="state"
				<?php echo "value=\"". strhtml($school->state)."\""?> maxlength="32"
				size="24" /></td>
			<td class="form_text"><label for="in_zip">Postal Code:</label><input
				id="in_zip" name="zip"
				<?php echo "value=\"". strhtml($school->zip)."\""?> maxlength="16"
				size="10" /></td>
		</tr>
	</tbody>
</table>
				<?php }?>
