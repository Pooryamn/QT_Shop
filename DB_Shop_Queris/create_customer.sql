CREATE TABLE Customers (
	"Customer ID"	SERIAL,
	Firstname	varchar(50) not null,
	Lastname	varchar(50) not null,
	Email		varchar(70) not null,
	"Phone number"	varchar(15),
	"Mobile number" varchar(20) not null,
	Address		text,
	city		varchar(30),
	"Postal code"	varchar(15),
	birthdate	date,
	Wallet		int,
	Attachments	bytea,
	Username	varchar(40) not null,

	primary key("Customer ID")
);
