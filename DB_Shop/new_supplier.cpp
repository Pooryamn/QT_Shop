#include "new_supplier.h"
#include "ui_new_supplier.h"

New_supplier::New_supplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_supplier)
{
    ui->setupUi(this);
}

New_supplier::~New_supplier()
{
    delete ui;
}
