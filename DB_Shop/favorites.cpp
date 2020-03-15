#include "favorites.h"
#include "ui_favorites.h"

favorites::favorites(QWidget *parent,int UsrID) :
    QDialog(parent),
    ui(new Ui::favorites)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    USER_ID = UsrID;

    load_data(USER_ID);
}

favorites::~favorites()
{
    DB.Disconnect();
    delete ui;
}

void favorites::load_data(int id){

    QString query_str;
    QSqlQuery query;

    query_str = "select products.\"Product ID\",\"Product name\",category,"
                "\"Unit cost\",stock,\"Description\" "
                "from favorites inner join products on "
                "favorites.\"Product ID\" = products.\"Product ID\" "
                "where \"Customer ID\" = " + QString::number(id) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl << query.lastError();
        return;
    }

    model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Product");
    model->setHeaderData(2,Qt::Horizontal,"Category");
    model->setHeaderData(3,Qt::Horizontal,"Cost");
    model->setHeaderData(4,Qt::Horizontal,"Stock");
    model->setHeaderData(5,Qt::Horizontal,"Description");

    ui->tbl_history->setModel(model);

    ui->tbl_history->setColumnWidth(0,0);
    ui->tbl_history->setColumnWidth(1,150);
    ui->tbl_history->setColumnWidth(2,150);
    ui->tbl_history->setColumnWidth(3,100);
    ui->tbl_history->setColumnWidth(4,100);
    ui->tbl_history->setColumnWidth(5,420);

    ui->tbl_history->setSelectionMode(QAbstractItemView::SingleSelection);
}

void favorites::on_btn_delete_clicked()
{
    QItemSelectionModel *select = ui->tbl_history->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    QString query_str;
    QSqlQuery query;

    query_str = "delete from favorites where \"Product ID\" = "+QString::number(PRODUCT_ID) +
                " and \"Customer ID\" = "+ QString::number(USER_ID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl << query.lastError();
        return;
    }

    load_data(USER_ID);

}

void favorites::on_tbl_history_clicked(const QModelIndex &index)
{
    PRODUCT_ID = ui->tbl_history->model()->index(index.row(),0).data().toInt();
}
