CREATE TABLE Employee (
	"Employee ID"	SERIAL,
	Firstname	varchar(50) not null,
	Lastname	varchar(50) not null,
	"National ID"	varchar(12) not null,
	Email		varchar(70) not null,
	"Phone number"	varchar(15),
	"Mobile number"	varchar(20) not null,
	Address		text,
	city		varchar(30),
	"Postal code"	varchar(15),
	birthdate	date,
	Attachments	bytea,
	Username	varchar(40) not null,

	primary key("Employee ID") 
);