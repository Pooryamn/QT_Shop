#include "shop_history.h"
#include "ui_shop_history.h"

Shop_history::Shop_history(QWidget *parent,int usrid) :
    QDialog(parent),
    ui(new Ui::Shop_history)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Error conecting database";
        exit(0);
    }

    USER_ID = usrid;

    if(usrid != 0){
        load_data(USER_ID);
    }
    else{
        load_all();
    }

}

Shop_history::~Shop_history()
{
    DB.Disconnect();
    delete ui;
}

void Shop_history::load_data(int usrid){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Cart ID\",\"Total price\","
                "\"Pay status\",\"Pay date\" from "
                "cart where \"Customer ID\" = " + QString::number(usrid) +
                " and \"Pay status\" = 1;";


    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Price");
    model->setHeaderData(2,Qt::Horizontal,"Status");
    model->setHeaderData(3,Qt::Horizontal,"date");

    ui->tbl_history->setModel(model);

    ui->tbl_history->setColumnWidth(0,150);
    ui->tbl_history->setColumnWidth(1,150);
    ui->tbl_history->setColumnWidth(2,200);
    ui->tbl_history->setColumnWidth(3,200);

    ui->tbl_history->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Shop_history::load_all(){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Cart ID\",concat(firstname , \' \' , lastname) as fullname,"
                "\"Pay date\",\"Total price\" from cart inner join customers on cart.\"Customer ID\" = "
                "customers.\"Customer ID\" where \"Pay status\" = 1";


    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"full name");
    model->setHeaderData(2,Qt::Horizontal,"pay date");
    model->setHeaderData(3,Qt::Horizontal,"price");

    ui->tbl_history->setModel(model);

    ui->tbl_history->setColumnWidth(0,150);
    ui->tbl_history->setColumnWidth(1,300);
    ui->tbl_history->setColumnWidth(2,200);
    ui->tbl_history->setColumnWidth(3,200);

    ui->tbl_history->setSelectionMode(QAbstractItemView::SingleSelection);

}
