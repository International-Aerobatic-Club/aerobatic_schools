create table if not exists school
(
id int unsigned not null auto_increment primary key,
name varchar(256),
addressLine1 varchar(256),
addressLine2 varchar(256),
city char(32),
state char(32),
country char(32),
zip char(16),
contact char(64),
phone char(16),
fax char(16),
email varchar(256),
web varchar(256),
aircraft varchar(256),
notes varchar(256),
course set('tailwheel', 'spinRecovery', 'emergencyUpset', 'basicAerobatics', 'advancedAerobatics', 'competitionCritique', 'aerobaticRides', 'formation', 'airCombat', 'CFI_spinEndorsement', 'RVaerobatics', 'glider'),
airport char(4),
airCity char(32),
airState char(32)
);

create table if not exists instructor
(
id int unsigned not null auto_increment primary key,
schoolID int unsigned not null,
givenName char(32),
sirName char(32),
cert enum('none','FI-A','CFI','CFI-A','MCFI','MCFI-A') not null default 'none',
isACE enum('y', 'n') not null default 'n',
constraint foreign key inst_schl (schoolID) references school (id) on delete cascade on update restrict
);

create table if not exists location
(
id int unsigned not null auto_increment primary key,
schoolID int unsigned not null,
airportID char(4),
name char(64),
city char(32),
state char(32),
isInternational char(1) not null default 'n',
constraint foreign key loc_schl (schoolID) references school (id) on delete cascade on update restrict
);
