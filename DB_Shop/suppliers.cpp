#include "suppliers.h"
#include "ui_suppliers.h"

Suppliers::Suppliers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Suppliers)
{
    ui->setupUi(this);
}

Suppliers::~Suppliers()
{
    delete ui;
}

void Suppliers::on_btn_addsupplier_clicked()
{
    New_supplier* supplier = new New_supplier(this);
    supplier->setFixedSize(supplier->width(),supplier->height());
    supplier->exec();
}
