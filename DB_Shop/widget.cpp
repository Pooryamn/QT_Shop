#include "widget.h"
#include "ui_widget.h"



using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Check_Connection();

    Setup();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::Setup(){

    // Set Not found picture on mini pic1
    ui->pic_1->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(65,65,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_2->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(60,65,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic3
    ui->pic_3->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(65,65,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_4->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(60,65,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_5->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(60,65,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_6->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(60,65,Qt::KeepAspectRatio));


    // Set Not found picture on Big pic
    ui->pic_0->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(300,300,Qt::KeepAspectRatio));

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
    this->close();
    registering->exec();
}
