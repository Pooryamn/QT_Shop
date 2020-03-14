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

    supplier_called = false;

    load_suppliers();
}

new_stock::~new_stock()
{
    DB.Disconnect();
    delete ui;
}

void new_stock::on_btn_addsupplier_clicked()
{
    supplier_called = true;

    this->close();

    /*
    New_supplier* supplier = new New_supplier(this,0,0);
    supplier->setFixedSize(supplier->width(),supplier->height());
    DB.Disconnect();
    supplier->exec();
    DB.Connect();
    */
}

void new_stock::load_suppliers(){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company name\" from suppliers";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"Company name");

    ui->tbl_supplier->setModel(model);

    ui->tbl_supplier->setColumnWidth(0,180);

    ui->tbl_supplier->setSelectionMode(QAbstractItemView::SingleSelection);
}


bool new_stock::new_supplier_called(){
    return supplier_called;
}
