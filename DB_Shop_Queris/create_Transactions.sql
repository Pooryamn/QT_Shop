CREATE TABLE Transactions(
	"Transaction ID"	SERIAL,
	"Customer ID"		integer not null,
	"Transaction type"	varchar(20) not null,
	"Transaction amount"	integer not null,
	"Transaction status"	varchar(20) not null,

	primary key("Transaction ID"),
	foreign key("Customer ID") references Customers
);