#include "user_payment.h"
#include "ui_user_payment.h"

user_payment::user_payment(QWidget *parent,QString usrname) :
    QDialog(parent),
    ui(new Ui::user_payment)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Error conecting database";
        exit(0);
    }

    UserName = usrname;

    //load_data(UserName);
}

user_payment::~user_payment()
{
    delete ui;
}

void user_payment::on_btn_addpayment_clicked()
{
    gateway* gtway = new gateway(this);
    gtway->setFixedSize(gtway->width(),gtway->height());
    gtway->exec();
    int ammount = gtway->get_ammount();

    if(ammount == 0){
        return;
    }

    int ID = find_id(UserName);

    //get date :
    int year,month,day;
    QDate::currentDate().getDate(&year,&month,&day);
    QString pay_date = QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day);

    add_transaction(ID,ammount,pay_date);
}

int user_payment::find_id(QString username){
    QString query_str;
    QSqlQuery query;

    query_str = "select \"Customer ID\" "
                "from customers where "
                "username = "
                "\'"+username+"\' ;";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        exit(0);
    }

    query.first();

    return query.value(0).toInt();

}

bool user_payment::add_transaction(int id, int ammount, QString date){

    QString query_str;
    QSqlQuery query;

}

