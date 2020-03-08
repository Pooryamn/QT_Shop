CREATE TABLE Products(
	"Product ID"	SERIAL,
	"Supplier ID"	integer,
	"Product name"	varchar(40),
	Category	varchar(30),
	"Unit cost"	integer,
	Stock		integer,

	primary key("Product ID"),
	foreign key("Supplier ID") references Suppliers
);