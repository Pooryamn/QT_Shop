CREATE TABLE Favorites(
	"Customer ID"	integer,
	"Product ID"	integer,

	primary key("Customer ID","Product ID"),
	foreign key("Customer ID") references Customers,
	foreign key("Product ID") references Products
);