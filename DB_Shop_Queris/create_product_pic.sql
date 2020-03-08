CREATE TABLE Product_PIC(
	ID		SERIAL,
	"Product ID"	integer,
	Attachments	bytea,

	primary key(ID),
	foreign key("Product ID") references Products
);	