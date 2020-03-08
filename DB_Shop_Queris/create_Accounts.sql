CREATE TABLE Account(
	Username	varchar(30) not null,
	"Password"	varchar(40) not null,
	"Account type"	integer not null,

	primary key(Username)
);	