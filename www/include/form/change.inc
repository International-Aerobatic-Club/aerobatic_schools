<?php
require_once('toolkit/encodeHTML.inc');
require_once('toolkit/encodeSQL.inc');

$changeTypes = array('add', 'remove', 'update');

function changeTypeFormEntry($post)
{
   global $changeTypes;
   echo '<tr>';
   echo '<td class="form_select"><label for="in_change">Type of change:</label>';
   echo '<fieldset id="in_change">';
   foreach ($changeTypes as $ct) {
   echo '<div class="select_item"><input class="form_select"';
   echo 'id="in_change_add" type="radio" name="change" value="'.$ct.'" '.isSelected($post,'change',$ct).'/><label for="in_change_add">'.$ct.'</label></div>';
   }
   echo '</td>';
   echo '</tr>';
}
?>