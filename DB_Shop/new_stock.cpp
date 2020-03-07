#include "new_stock.h"
#include "ui_new_stock.h"

new_stock::new_stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_stock)
{
    ui->setupUi(this);
}

new_stock::~new_stock()
{
    delete ui;
}

void new_stock::on_btn_addsupplier_clicked()
{
    New_supplier* supplier = new New_supplier(this);
    supplier->setFixedSize(supplier->width(),supplier->height());
    supplier->exec();
}
