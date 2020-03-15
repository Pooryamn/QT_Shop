#include "widget.h"
#include "ui_widget.h"



using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Check_Connection();

    Connect_DB();

    Setup();

    //label_connection();

    Search(ui->txt_search->text(),0);
}

Widget::~Widget()
{
    DB.Disconnect();
    delete ui;
}

void Widget::Setup(){

    // Set Not found picture on mini pic1
    ui->pic_1->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_1->setIconSize(ui->pic_1->size());


    // Set Not found picture on mini pic2
    ui->pic_2->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_2->setIconSize(ui->pic_1->size());

    // Set Not found picture on mini pic3
    ui->pic_3->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_3->setIconSize(ui->pic_1->size());

    // Set Not found picture on mini pic2
    ui->pic_4->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_4->setIconSize(ui->pic_1->size());

    // Set Not found picture on mini pic2
    ui->pic_5->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_5->setIconSize(ui->pic_1->size());

    // Set Not found picture on mini pic2
    ui->pic_6->setIcon(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));
    ui->pic_6->setIconSize(ui->pic_1->size());

    // Set Not found picture on Big pic
    ui->pic_0->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(200,200,Qt::KeepAspectRatio));

    //
    ui->txt_description->setReadOnly(true);

}

void Widget::Check_Connection(){

    /// this function is for internet connection check

    QNetworkAccessManager manager;

    QNetworkRequest req(QUrl("http://www.google.com"));

    QNetworkReply* reply = manager.get(req);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (!reply->bytesAvailable()){
        QMessageBox::warning(this,"Connection Error","Make sure you are connected to the internet.Try again");
        exit(0);
    }
}

void Widget::on_btn_help_clicked()
{
    Help hlp(this);
    hlp.setFixedSize(hlp.width(),hlp.height());
    hlp.exec();
}

void Widget::on_btn_register_clicked()
{ 
    delete model;
    SignUp *registering = new SignUp(0);
    registering->setGeometry(500,200,this->width(),this->height());
    registering->setFixedSize(this->width(),this->height());
    DB.Disconnect();
    this->close();
    registering->exec();
    this->show();
    DB.Connect();
    Search(ui->txt_search->text(),0);
}

void Widget::on_btn_login_clicked()
{
    delete model;
    DB.Disconnect();
    Loging* login = new Loging(this);
    login->setFixedSize(login->width(),login->height());
    this->close();
    login->exec();

    int user_type = login->get_type();
    QString username = login->get_user();
    if(user_type == 0){
        // Nothing :
        this->show();
        DB.Connect();
        Search(ui->txt_search->text(),0);
    }
    else if(user_type == 1){
        // User type :
        DB.Disconnect();
        user_part* user = new user_part(0,username);
        user->setGeometry(500,200,1000,720);
        user->on_btn_resizer_clicked();
        this->close();
        user->exec();
    }
    else if (user_type == 2) {
        // Employee type :
        DB.Disconnect();
        employee_part* emp = new employee_part(this,username);
        emp->setGeometry(500,200,1000,720);
        emp->on_btn_resizer_clicked();
        this->close();
        emp->exec();
    }
    else if(user_type == 3){
        // Master type:
        master_part* master = new master_part(0,username);
        master->setGeometry(500,200,1000,720);
        master->on_btn_resizer_clicked();
        this->close();
        master->exec();
    }
}

void Widget::on_txt_search_textChanged(const QString &arg1)
{
    if(ui->radio_Name->isChecked()){
        Search(arg1,0);
    }
    else{
        Search(arg1,1);
    }
}

void Widget::Connect_DB(){

    /// This function do these tasks :
    /// 1) try to connect to database
    /// 2) find connection problems
    /// 3) handle connection problems

    int Connection_result = DB.Connect();

    if(Connection_result == 0){
        // No Problem
        return;
    }
    else if(Connection_result == 1){

        // Driver problem
        QMessageBox::warning(this,"Database Connection Error","Postqresql Driver(QPSQL) not found");
        exit(0);
    }
    else if(Connection_result == 2){

        // database file problem
        QMessageBox::warning(this,"Database Connection Error","Database file not found");
        exit(0);
    }

}

void Widget::Search(QString key, int Type){

    QString query_str;
    QSqlQuery query;

    if(Type == 0){
        // search by name}
        if(key.isEmpty()){
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products;";
        }
        else {

            query_str = "select \"Product ID\",\"Product name\" "
                        "from products where \"Product name\" like \'%" + key +"%\'";
        }
    }
    else {
        // serch by category
        if(key.remove(" ").isEmpty()){
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products;";
        }
        else{
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products where category like \'%" + key +"%\'";

        }
    }
    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    model = new QSqlQueryModel();

    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Productname");

    ui->tbl_search->setModel(model);

    ui->tbl_search->setColumnWidth(0,50);
    ui->tbl_search->setColumnWidth(1,190);

    ui->tbl_search->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Widget::load_search_data(int ID){

    QString query_str;
    QSqlQuery query;

    query_str = "select * from products where \"Product ID\" = "+ QString::number(ID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    query.first();

    QString Pname = query.value(2).toString();
    QString Cname = find_company(query.value(1).toInt());
    QString Category = query.value(3).toString();
    QString UnitCost = query.value(4).toString();
    QString Stock = query.value(5).toString();
    QString Desc = query.value(6).toString();

    QString Html = "<h6>"
                    "<p style= \"color : #FF0000 \" ; >  Product Name : </p>"
                    "<p style= \"color : #1010FF \" ; > " + Pname +  " </p> "
                    "<p style= \"color : #FF0000 \" ; >  Company : </p>"
                    "<p style= \"color : #1010FF \" ; > " + Cname + " </p> "
                    "<p style= \"color : #FF0000 \" ; >  Category : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Category +  "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Cost : </p> "
                    "<p style= \"color : #1010FF \" ; > " + UnitCost + "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Stock : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Stock + "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Description : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Desc + "</p>"
                    "<br>"
                    "</h6>";

    ui->txt_description->setHtml(Html);

    // pics :
    query_str.clear();
    query.clear();

    query_str = "select * from product_pic where \"Product ID\" = " + QString::number(ID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return ;
    }

    Setup();

    for(int i = 0;i<6;i++){
        image[i].clear();
    }

    query.first();

    for (int i = 0;i<query.size();i++) {
        image[i] = query.value(2).toByteArray();
        query.next();
    }

    if(image[0].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[0],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
        ui->pic_0->setPixmap(pixx);

        ui->pic_1->setIcon(pixx);
        ui->pic_1->setIconSize(ui->pic_1->size());
        ui->pic_1->setStyleSheet("background-color: rgb(255, 255, 255);");

    }

    if(image[1].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[1],nullptr,Qt::AutoColor);
        ui->pic_2->setIcon(pixx);
        ui->pic_2->setIconSize(ui->pic_1->size());
        ui->pic_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    }


    if(image[2].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[2],nullptr,Qt::AutoColor);
        ui->pic_3->setIcon(pixx);
        ui->pic_3->setIconSize(ui->pic_1->size());
        ui->pic_3->setStyleSheet("background-color: rgb(255, 255, 255);");

    }


    if(image[3].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[3],nullptr,Qt::AutoColor);
        ui->pic_4->setIcon(pixx);
        ui->pic_4->setIconSize(ui->pic_1->size());
        ui->pic_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    }


    if(image[4].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[4],nullptr,Qt::AutoColor);
        ui->pic_5->setIcon(pixx);
        ui->pic_5->setIconSize(ui->pic_1->size());
        ui->pic_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    }


    if(image[5].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[5],nullptr,Qt::AutoColor);
        ui->pic_6->setIcon(pixx);
        ui->pic_6->setIconSize(ui->pic_1->size());
        ui->pic_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

}

QString Widget::find_company(int id){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company name\" from suppliers"
                " inner join products on suppliers.\"Supplier ID\" "
                "= products.\"Supplier ID\" "
                "where suppliers.\"Supplier ID\" = " + QString::number(id)+ ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return "";
    }

    query.first();

    return query.value(0).toString();
}

void Widget::on_tbl_search_clicked(const QModelIndex &index)
{
    int id = ui->tbl_search->model()->index(index.row(),0).data().toInt();
    load_search_data(id);
}


void Widget::on_pic_1_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[0],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}

void Widget::on_pic_2_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[1],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}

void Widget::on_pic_3_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[2],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}

void Widget::on_pic_4_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[3],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}

void Widget::on_pic_5_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[4],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}

void Widget::on_pic_6_clicked()
{
    QPixmap pixx;
    pixx.loadFromData(image[5],nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
    ui->pic_0->setPixmap(pixx);
}
