<?php
require_once('toolkit/useful.inc');
require_once('toolkit/encodeSQL.inc');

class Instructor {
   var $id;
   var $schoolID;
   var $givenName;
   var $sirName;
   var $cert;
   var $isACE;

   function getCertValues()
   {
      return array('none','FI-A','CFI','CFI-A','MCFI','MCFI-A');
   }

   function validatePost($post)
   {
      //      debugArr("instructor post data", $post);
      $corrMsg = "";
      $this->id = $post['id'];
      $this->schoolID = $post['schoolID'];
      $this->givenName = crop($post['givenName'],32);
      if ($this->givenName == '')
      {
         $corrMsg .= '<li>Provide the instructor\'s given name.</li>';
      }
      $this->sirName = crop($post['sirName'],32);
      if ($this->givenName == '')
      {
         $corrMsg .= '<li>Provide the instructor\'s family name.</li>';
      }
      $isCFI = checked($post['ratings_CFI']);
      $isFIA = checked($post['ratings_FIA']);
      $isMCFI = checked($post['ratings_MCFI']);
      $this->cert = $this->computeCert($isCFI, $isFIA, $isMCFI);
      $this->isACE = checked($post['ratings_ACE']);
      //      debug('Instructors result');
      //      foreach ($this as $key => $value)
      //      {
      //         debug($key.':'.$value.':', false);
      //      }
      //      debug("validateInstructor says, '".$corrMsg."'");
      return $corrMsg;
   }

   function instructorExists($db_conn)
   {
      $haveSetting = false;
      $query = 'select schoolID from instructor';
      $query .= " where id = " . intSQL($this->id);
      //debug($query);
      $result = dbQuery($db_conn, $query);
      if (dbErrorNumber() != 0)
      {
         notifyError(dbErrorText(), 'instructor->instructorExists');
      } else
      {
         $haveSetting = (dbCountResult($result) != 0);
      }
      return $haveSetting;
   }

   function createOrUpdateRecord($db_conn)
   {
      //debugArr('school.createOrUpdateRecord, data is ', $this);
      $insert = FALSE;
      if ($this->instructorExists($db_conn))
      {
         $query = 'update instructor set ' .
         $query .= 'givenName = '.strSQL($this->givenName,32).',';
         $query .= 'sirName = '.strSQL($this->sirName,32).',';
         $query .= "cert = '".$this->cert."',";
         $query .= "isACE = '".($this->isACE?'y':'n')."'";
         $query .= ' where id = ' . intSQL($this->id);
      } else
      {
         $insert = TRUE;
         $query = 'insert into instructor(schoolID,givenName,sirName,cert,isACE) values (';
         $query .= intSQL($this->schoolID).',';
         $query .= strSQL($this->givenName,32).',';
         $query .= strSQL($this->sirName,32).',';
         $query .= "'".$this->cert."',";
         $query .= "'".($this->isACE?'y':'n')."'";
         $query .= ')';
      }
      //debug('school query ' . $query);
      $result = dbExec($db_conn, $query);
      //debug('school query result '.$result);
      if ($result == '' && $insert) $this->id = dbLastID();
      return $result;
   }

   function extractRecord($row)
   {
      $this->id = $row['id'];
      $this->schoolID = $row['schoolID'];
      $this->givenName = $row['givenName'];
      $this->sirName = $row['sirName'];
      $this->cert = $row['cert'];
      $this->isACE = $row['isACE'] == 'y';
   }

   function readRecord($db_conn, $id)
   {
      $success = FALSE;
      $query = "select * from instructor where id=";
      $query .= intSQL($id);
      //debug('instructor->readRecord query is '.$query);
      $dbResult = dbQuery($db_conn, $query);
      if ($dbResult)
      {
         $row = dbFetchAssoc($dbResult);
         if ($row)
         {
            $success = true;
            $this->extractRecord($row);
         }
      }
      return $success ? '' : dbErrorText();
   }
    
   function deleteRecord($db_conn, $id)
   {
      $query = "delete from instructor where id=";
      $query .= intSQL($id);
      $success =  dbExec($db_conn, $query);
      return $success ? '' : dbErrorText();
   }

   function isCFI()
   {
      return isSet($this->cert) && $this->cert != 'none' && $this->cert != 'FI-A';
   }

   function isFIA()
   {
      return $this->cert == 'FI-A' || $this->cert == 'CFI-A' || $this->cert == 'MCFI-A';
   }

   function isMCFI()
   {
      return $this->cert == 'MCFI' || $this->cert == 'MCFI-A';
   }

   function computeCert($isCFI, $isFIA, $isMCFI)
   {
      //debug('computeCert('.$isCFI.','.$isFIA.','.$isMCFI.')');
      $cert = 'none';
      if ($isMCFI){
         //debug('computeCert is MCFI');
         $cert = ($isFIA ? 'MCFI-A' : 'MCFI');
      }
      else if ($isCFI){
         //debug('computeCert is CFI');
         $cert = ($isFIA ? 'CFI-A' : 'CFI');
      }
      else {
         //debug('computeCert not CFI');
         $cert = ($isFIA ? 'FI-A' : 'none');
      }
      //debug('computeCert has '.$cert);
      return $cert;
   }
    
   function printData()
   {
      //      debug('instructor.printData '.$this->cert);
      $data = 'Instructor '.$this->givenName.' '.$this->sirName."\n";
      if ($this->isCFI()) $data .= "is a CFI\n";
      if ($this->isFIA()) $data .= "is an Aerobatic Instructor\n";
      if ($this->isMCFI()) $data .= "is a Master CFI\n";
      if ($this->isACE) $data .= "is an ICAS Aerobatic Comepetency Evaluator (A.C.E.)\n";
      return $data;
   }
}
?>
