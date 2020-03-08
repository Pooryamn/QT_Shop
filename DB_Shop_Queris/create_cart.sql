CREATE TABLE Cart(
	"Cart ID"	SERIAL,
	"Customer ID"	integer not null,
	"Total price"	integer not null,
	"Create date"	date,
	"Pay date"	date,
	"Pay status"	integer,

	primary key("Cart ID"),
	foreign key("Customer ID") references Customers
);