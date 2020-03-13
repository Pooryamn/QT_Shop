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

    if(get_type(UserName) == 1){
        load_data(UserName);
    }
    else{
        load_all();
        ui->btn_addpayment->setVisible(false);
    }
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

    QString pay_date = DateConverter();

    if(add_transaction(ID,ammount,pay_date)){
        add_wallet(ID,ammount);
    }

    load_data(UserName);
}

int user_payment::find_id(QString username){
    QString query_str;
    QSqlQuery query;

    query_str = "select \"Customer ID\" "
                "from customers where "
                "username = "
                "\'" + username+"\' ;";

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

    query_str = "insert into transactions("
                "\"Customer ID\" , \"Transaction type\","
                "\"Transaction amount\",\"Transaction status\","
                "\"Transaction date\") values"
                "(" + QString::number(id) + ", \'Pay\',"
                +QString::number(ammount) + ", \'successful\' ,"
                "\'" + date + "\' );";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return false;
    }
    return true;

}

QString user_payment::DateConverter(){

    //get date:
    int year,month,day;
    QDate::currentDate().getDate(&year,&month,&day);
    QString pay_date = QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day);

    QDateConvertor convert;
    QStringList shamsi_list = convert.ToJalali(QString::number(year),QString::number(month),QString::number(day));

    QString result = shamsi_list[0] + "-" + shamsi_list[1] + "-" + shamsi_list[2];

    qDebug() << result;

    return result;
}

bool user_payment::add_wallet(int ID, int ammount){

    QString query_str;
    QSqlQuery query;

    query_str = "update customers set "
                "wallet = wallet + "
                + QString::number(ammount)+
                " where \"Customer ID\" = " +
                QString::number(ID) + ";";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

void user_payment::load_data(QString username){

    int ID = find_id(username);

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Transaction ID\",\"Transaction type\","
                "\"Transaction amount\",\"Transaction status\","
                "\"Transaction date\" from transactions where "
                "\"Customer ID\" = " + QString::number(ID) + " ;";


    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Transaction type");
    model->setHeaderData(2,Qt::Horizontal,"amount");
    model->setHeaderData(3,Qt::Horizontal,"status");
    model->setHeaderData(4,Qt::Horizontal,"date");

    ui->tbl_payment->setModel(model);

    ui->tbl_payment->setColumnWidth(0,150);
    ui->tbl_payment->setColumnWidth(1,150);
    ui->tbl_payment->setColumnWidth(2,200);
    ui->tbl_payment->setColumnWidth(3,200);
    ui->tbl_payment->setColumnWidth(4,200);

    ui->tbl_payment->setSelectionMode(QAbstractItemView::SingleSelection);
}

int user_payment::get_type(QString username){

    QSqlQuery query;
    QString query_str;

    query_str = "select \"Account type\" "
                "from account "
                "where "
                "username = \'" + username + "\' ;" ;

    if(DB.Execute(query_str,query) ==false){
        qDebug() <<query.lastError();
    }

    query.first();

    return query.value(0).toInt();
}

void user_payment::load_all(){
    QString query_str;
    QSqlQuery query;

    query_str = "select \"Transaction ID\",\"Transaction type\","
                "\"Transaction amount\",\"Transaction status\","
                "\"Transaction date\" from transactions ;";


    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Transaction type");
    model->setHeaderData(2,Qt::Horizontal,"amount");
    model->setHeaderData(3,Qt::Horizontal,"status");
    model->setHeaderData(4,Qt::Horizontal,"date");

    ui->tbl_payment->setModel(model);

    ui->tbl_payment->setColumnWidth(0,150);
    ui->tbl_payment->setColumnWidth(1,150);
    ui->tbl_payment->setColumnWidth(2,200);
    ui->tbl_payment->setColumnWidth(3,200);
    ui->tbl_payment->setColumnWidth(4,200);

}
