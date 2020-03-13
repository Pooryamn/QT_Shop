#include "new_stock.h"
#include "ui_new_stock.h"

new_stock::new_stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_stock)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database connection error";
        exit(0);
    }

    load_suppliers();
}

new_stock::~new_stock()
{
    DB.Disconnect();
    delete ui;
}

void new_stock::on_btn_addsupplier_clicked()
{
    DB.Disconnect();
    New_supplier* supplier = new New_supplier(this,0);
    supplier->setFixedSize(supplier->width(),supplier->height());
    supplier->exec();
    DB.Connect();
}

void new_stock::load_suppliers(){

}
