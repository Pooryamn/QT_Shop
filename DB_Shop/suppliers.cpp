#include "suppliers.h"
#include "ui_suppliers.h"

Suppliers::Suppliers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Suppliers)
{
    ui->setupUi(this);

    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    Load_data();

}

Suppliers::~Suppliers()
{
    DB.Disconnect();
    delete ui;
}

void Suppliers::on_btn_addsupplier_clicked()
{
    New_supplier* supplier = new New_supplier(this,0,0);
    supplier->setFixedSize(supplier->width(),supplier->height());
    DB.Disconnect();
    supplier->exec();
    DB.Connect();
}

void Suppliers::on_btn_deletesupplier_clicked()
{
    QItemSelectionModel *select = ui->tbl_suppliers->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    QModelIndex idx =  select->currentIndex();
    int row = idx.row();

    int ID = ui->tbl_suppliers->model()->index(row,0).data().toInt();

    QString query_str;
    QSqlQuery query;

    query_str = "delete from suppliers where "
                "\"Supplier ID\" = " + QString::number(ID) + ";";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    Load_data();
}

void Suppliers::Load_data(){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Supplier ID\",\"Company name\", "
                "email,phone,\"Company Type\" from suppliers ;";

    if(DB.Execute(query_str,query) == false){

        qDebug() << query.lastQuery() << endl << query.lastError();
        exit(0);
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Company name");
    model->setHeaderData(2,Qt::Horizontal,"Email");
    model->setHeaderData(3,Qt::Horizontal,"Phone");
    model->setHeaderData(4,Qt::Horizontal,"Category");

    ui->tbl_suppliers->setModel(model);

    ui->tbl_suppliers->setColumnWidth(0,150);
    ui->tbl_suppliers->setColumnWidth(1,200);
    ui->tbl_suppliers->setColumnWidth(2,200);
    ui->tbl_suppliers->setColumnWidth(3,200);
    ui->tbl_suppliers->setColumnWidth(4,150);

    ui->tbl_suppliers->setSelectionMode(QAbstractItemView::SingleSelection);
}
