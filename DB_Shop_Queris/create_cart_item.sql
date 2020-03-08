CREATE TABLE Cart_item(
	"Cart ID"	integer,
	"Product ID"	integer,
	Quantity	integer,
	"Unit cost"	integer,

	primary key("Cart ID","Product ID"),
	foreign key("Cart ID") references Cart,
	foreign key("Product ID") references Products 
);