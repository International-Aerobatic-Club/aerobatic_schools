<?php
function instructorAnchor($id)
{
   return 'instr_'.$id;
}

function schoolAnchor($id)
{
   return 'sid_'.$id;
}

function stateAnchor($state, $country)
{
   return 'state_'.$state.'_'.$country;
}

function displayLoc($city, $state, $country)
{
   $lc = trim($city);
   $ls = trim($state);
   if ($lc != '' && $ls != '')
   {
      $ls = ', ' . $ls;
   }
   $ln = trim($country);
   if (($ls != '' || $lc != '') && $ln != '')
   {
      $ln = ', ' . $ln;
   }
   return $lc . $ls . $ln;
}
?>