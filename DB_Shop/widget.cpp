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

}

Widget::~Widget()
{
    delete ui;
}

void Widget::Setup(){

    // Set Not found picture on mini pic1
    ui->pic_1->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_2->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic3
    ui->pic_3->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_4->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_5->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_6->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));


    // Set Not found picture on Big pic
    ui->pic_0->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(200,200,Qt::KeepAspectRatio));

    //
    ui->txt_description->setDisabled(true);

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
    SignUp *registering = new SignUp(0);
    registering->setGeometry(500,200,this->width(),this->height());
    registering->setFixedSize(this->width(),this->height());
    DB.close();
    this->close();
    registering->exec();
}

void Widget::on_btn_login_clicked()
{
    Loging* login = new Loging(this);
    login->setFixedSize(login->width(),login->height());
    login->exec();
}

void Widget::on_txt_search_textChanged(const QString &arg1)
{
    if(arg1 == "___1"){
        user_part* user = new user_part(0);
        user->setGeometry(500,200,1000,720);
        user->on_btn_resizer_clicked();
        user->exec();
    }
    else if (arg1 == "___2") {
        employee_part* emp = new employee_part(0);
        emp->setGeometry(500,200,1000,720);
        emp->on_btn_resizer_clicked();
        emp->exec();
    }
    else if (arg1 == "___3") {
        master_part* master = new master_part(0);
        master->setGeometry(500,200,1000,720);
        master->on_btn_resizer_clicked();
        master->exec();

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
