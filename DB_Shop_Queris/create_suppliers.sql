CREATE TABLE Suppliers(
	"Supplier ID"	SERIAL,
	"Company name"	varchar(30) not null,
	Email 		varchar(70) not null,
	Phone 		varchar(20),
	"Company Type"	varchar(30) not null,
	Attachments	bytea,

	primary key("Supplier ID") 
);