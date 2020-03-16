#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    load_data(ui->combo_type->currentText());

}

Users::~Users()
{
    DB.Disconnect();
    delete ui;
}

void Users::load_data(QString type){

    QString query_str;
    QSqlQuery query;

    if(type == "All"){
        query_str = "( select firstname,lastname,username,email,"
                    "\"Mobile number\", birthdate from "
                    "customers )"
                    "union"
                    "( select firstname,lastname,account.username,email,"
                    "\"Mobile number\",birthdate from "
                    "employee inner join account on "
                    "employee.username = account.username "
                    "where account.\"Account type\" = 2 ); ";
    }
    else if(type == "Customers"){

        query_str = "( select firstname,lastname,username,email,"
                    "\"Mobile number\", birthdate from "
                    "customers );";
    }
    else{
        query_str = "( select firstname,lastname,account.username,email,"
                    "\"Mobile number\",birthdate from "
                    "employee inner join account on "
                    "employee.username = account.username "
                    "where account.\"Account type\" = 2 ); ";
    }

    if(DB.Execute(query_str,query) == false){

        qDebug() << query.lastQuery() << endl << query.lastError();
        exit(0);
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,"Firstname");
    model->setHeaderData(1,Qt::Horizontal,"Lastname");
    model->setHeaderData(2,Qt::Horizontal,"Username");
    model->setHeaderData(3,Qt::Horizontal,"Email");
    model->setHeaderData(4,Qt::Horizontal,"Mobile number");
    model->setHeaderData(5,Qt::Horizontal,"Birthdate");

    ui->tbl_users->setModel(model);

    ui->tbl_users->setColumnWidth(0,150);
    ui->tbl_users->setColumnWidth(1,150);
    ui->tbl_users->setColumnWidth(2,150);
    ui->tbl_users->setColumnWidth(3,200);
    ui->tbl_users->setColumnWidth(4,130);
    ui->tbl_users->setColumnWidth(5,120);

    ui->tbl_users->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Users::on_combo_type_currentIndexChanged(const QString &arg1)
{
    load_data(arg1);
}

void Users::on_btn_deleteuser_clicked()
{
    QItemSelectionModel *select = ui->tbl_users->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    QModelIndex idx =  select->currentIndex();
    int row = idx.row();

    QString usr = ui->tbl_users->model()->index(row,2).data().toString();

    QSqlQuery query;
    QString query_str;

    query_str = "select \"Account type\" from account where username = \'" + usr +"\' ;";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    query.first();

    int Type = query.value(0).toInt();

    query.clear();
    query_str.clear();

    if(Type == 1){
        query_str = "delete from customers where username = \'" + usr +"\' ;";

        if(DB.Execute(query_str,query) ==false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
        }
    }
    else{
        query_str = "delete from employee where username = \'" + usr +"\' ;";

        if(DB.Execute(query_str,query) ==false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
        }
    }

    query.clear();
    query_str.clear();

    query_str = "delete from account where username = \'" + usr +"\' ;";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
    }

    load_data(ui->combo_type->currentText());

}

