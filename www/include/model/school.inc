<?php
require_once('toolkit/useful.inc');
require_once('toolkit/encodeSQL.inc');

class School {
   var $id;
   var $name;
   var $addressLine1;
   var $addressLine2;
   var $city;
   var $state;
   var $zip;
   var $contact;
   var $phone;
   var $fax;
   var $email;
   var $web;
   var $aircraft;
   var $notes;
   var $courses;
   var $country;
   var $airport;
   var $airCity;
   var $airState;

   static $courseValues = array(
        'tailwheel','spin','upset','basicAerobatics','advancedAerobatics','pitts','RVaerobatics','glider');

   static $courseDescriptions = array(
   'tailwheel' => 'Tailwheel endorsement',
   'spin' => 'Stall/spin recovery',
   'upset' => 'Unusual attitude/upset training',
   'basicAerobatics' => 'Recreational aerobatics',
   'advancedAerobatics' => 'Competition aerobatics',
   'pitts' => 'Pitts checkout',
   'RVaerobatics' => 'RV aerobatics',
   'glider' => 'Glider aerobatics');

   /**
    * Corvert SQL format course selection into array of description strings
    * @param $cv SQL format course selection, e.g. "'tailwheel','basicAerobatics'"
    * @return array of string
    */
   static function courseValueDescription($cv)
   {
      $courses = array();
      if ($cv != '')
      {
         $cva = explode(",", $cv);
         foreach ($cva as $crs)
         {
            $courses[] = School::$courseDescriptions[$crs];
         }
      }
      return $courses;
   }

   function validatePost($post, $abbrev=false)
   {
      //      debugArr("school post data", $post);
      $corrMsg = "";
      $this->id = $post['id'];
      $this->name = crop($post['name'],256);
      if ($this->name == '')
      {
         $corrMsg .= '<li>The name of the school must not be blank.</li>';
      }
      $this->addressLine1 = crop($post['addressLine1'], 256);
      $this->addressLine2 = crop($post['addressLine2'], 256);
      $this->airport = crop($post['airport'], 4);
      if (!$abbrev && $this->airport == '')
      {
         $corrMsg .= '<li>Please supply the school location airport three or four letter ID.</li>';
      }
      $this->airCity = crop($post['airCity'], 32);
      if ($this->airCity == '')
      {
         $corrMsg .= '<li>Please supply the school location city.</li>';
      }
      $this->airState = crop($post['airState'], 32);
      $this->zip = crop($post['zip'], 16);
      $this->contact = crop($post['contact'], 64);
      if ($this->contact == '')
      {
         $corrMsg .= '<li>Please supply a contact name for the school.</li>';
      }
      $this->phone = crop($post['phone'], 16);
      if ($this->phone == '')
      {
         $corrMsg .= '<li>Please supply a phone number for the school contact.</li>';
      }
      $this->fax = crop($post['fax'], 16);
      $this->email = crop($post['email'], 256);
      if (!validEmail($this->email))
      {
         $corrMsg .= '<li>Please supply a valid email address for the school contact.</li>';
      }
      $this->web = crop($post['web'], 256);
      $this->aircraft = crop($post['aircraft'], 256);
      $this->notes = crop($post['notes'], 256);
      $this->courses = selectionSet($post, 'course', School::$courseValues);
      $this->city = crop($post['city'], 32);
      $this->state = crop($post['state'], 32);
      $this->country = crop($post['country'], 32);
      if ($this->country == '')
      {
         // United states
         $this->state = strtoupper($this->state);
         if (!$abbrev && $this->airState == '')
         {
            $corrMsg .= '<li>Please supply either of the school location state or the country.</li>';
         }
         else
         {
            $this->airState = strtoupper($this->airState);
         }
      }
      //      debug('Schools result');
      //      foreach ($this as $key => $value)
      //      {
      //         debug($key.':'.$value.':', false);
      //      }
      //      debug("validateSchool says, '".$corrMsg."'");
      return $corrMsg;
   }

   function schoolExists($db_conn)
   {
      $haveSetting = false;
      $query = 'select name from school';
      $query .= " where id = " . intSQL($this->id);
      //      debug($query);
      $result = dbQuery($db_conn, $query);
      if (dbErrorNumber() != 0)
      {
         notifyError(dbErrorText(), 'school->schoolExists');
      } else
      {
         $haveSetting = (dbCountResult($result) != 0);
      }
      return $haveSetting;
   }

   function createOrUpdateRecord($db_conn)
   {
      // debug('school.createtOrUpdateRecord, data is '. $this->printData());
      $insert = FALSE;
      if ($this->schoolExists($db_conn))
      {
         $query = 'update school set ' .
         $query .= 'name = '.strSQL($this->name,256).',';
         $query .= 'addressLine1 = '.strSQL($this->addressLine1,256).',';
         $query .= 'addressLine2 = '.strSQL($this->addressLine2,256).',';
         $query .= 'city = '.strSQL($this->city,32).',';
         $query .= 'state = '.strSQL($this->state,2).',';
         $query .= 'zip = '.strSQL($this->zip,16).',';
         $query .= 'contact = '.strSQL($this->contact,64).',';
         $query .= 'phone = '.strSQL($this->phone,16).',';
         $query .= 'fax = '.strSQL($this->fax,16).',';
         $query .= 'email = '.strSQL($this->email,256).',';
         $query .= 'web = '.strSQL($this->web,256).',';
         $query .= 'aircraft = '.strSQL($this->aircraft,256).',';
         $query .= "course = '".$this->courses."',";
         $query .= 'notes = '.strSQL($this->notes,256).',';
         $query .= 'aircraft = '.strSQL($this->aircraft,256).',';
         $query .= 'airport = '.strSQL($this->airport,4).',';
         $query .= 'airCity = '.strSQL($this->airCity,32).',';
         $query .= 'airState = '.strSQL($this->airState,32).',';
         $query .= 'country = '.strSQL($this->country,32);
         $query .= ' where id = ' . intSQL($this->id);
      } else
      {
         $insert = TRUE;
         $query = 'insert into school(name,addressLine1,addressLine2,city,state,zip,contact,phone,fax,email,web,aircraft,course,country,notes,airport,airCity,airState) values (';
         $query .= strSQL($this->name,256).',';
         $query .= strSQL($this->addressLine1,256).',';
         $query .= strSQL($this->addressLine2,256).',';
         $query .= strSQL($this->city,32).',';
         $query .= strSQL($this->state,2).',';
         $query .= strSQL($this->zip,16).',';
         $query .= strSQL($this->contact,64).',';
         $query .= strSQL($this->phone,16).',';
         $query .= strSQL($this->fax,16).',';
         $query .= strSQL($this->email,256).',';
         $query .= strSQL($this->web,256).',';
         $query .= strSQL($this->aircraft,256).',';
         $query .= "'".$this->courses."',";
         $query .= strSQL($this->country,32).',';
         $query .= strSQL($this->notes,256).',';
         $query .= strSQL($this->airport,4).',';
         $query .= strSQL($this->airCity,32).',';
         $query .= strSQL($this->airState,32);
         $query .= ')';
      }
      // debug('school query ' . $query);
      $result = dbExec($db_conn, $query);
      // debug('school query result '.$result);
      if ($result == '' && $insert) $this->id = dbLastID();
      return $result;
   }

   function extractRecord($row)
   {
      $this->id = $row['id'];
      $this->name = $row['name'];
      $this->addressLine1 = $row['addressLine1'];
      $this->addressLine2 = $row['addressLine2'];
      $this->city = $row['city'];
      $this->state = $row['state'];
      $this->zip = $row['zip'];
      $this->contact = $row['contact'];
      $this->phone = $row['phone'];
      $this->fax = $row['fax'];
      $this->email = $row['email'];
      $this->web = $row['web'];
      $this->aircraft = $row['aircraft'];
      $this->notes = $row['notes'];
      $this->country = $row['country'];
      $this->courses = $row['course'];
      $this->airCity = $row['airCity'];
      $this->airState = $row['airState'];
      $this->airport = $row['airport'];
   }

   function readRecord($db_conn, $id)
   {
      $success = FALSE;
      $query = "select * from school where id=";
      $query .= intSQL($id);
      $dbResult = dbQuery($db_conn, $query);
      if ($dbResult)
      {
         $row = dbFetchAssoc($dbResult);
         if ($row)
         {
            $this->extractRecord($row);
            $success = TRUE;
         }
      }
      return $success ? '' : dbErrorText();
   }

   function printRef()
   {
      $ref = $this->name . ', ' . $this->airCity;
      if (isSet($this->airState) && $this->airState != '')
      {
         $ref .= ', '.$this->airState;
      }
      $ref .= "\nContact ".$this->contact.' at '.$this->phone.', email '.$this->email."\n\n";
      return $ref;
   }

   function printData()
   {
      $ref = $this->printRef();
      $ref .= "Country: $this->country\n";
      $ref .= "Airport: $this->airport\n";
      $ref .= "Airport City: $this->airCity\n";
      $ref .= "Airport State: $this->airState\n";
      $ref .= "Street Address: $this->addressLine1\n";
      $ref .= "Address line 2: $this->addressLine2\n";
      $ref .= "City: $this->city\n";
      $ref .= "State: $this->state\n";
      $ref .= "Zip: $this->zip\n";
      $ref .= "Contact: $this->contact\n";
      $ref .= "Phone: $this->phone\n";
      $ref .= "Fax: $this->fax\n";
      $ref .= "Email: $this->email\n";
      $ref .= "Web: $this->web\n";
      $ref .= "Aircraft: $this->aircraft\n";
      $ref .= "Notes: $this->notes\n";
      $ref .= "Courses: \n";
      $courses = School::courseValueDescription($this->courses);
      foreach ($courses as $course)
      {
         $ref .= " - $course\n";
      }
      return $ref;
   }
}
?>
