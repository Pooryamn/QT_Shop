#include "widget.h"
#include "ui_widget.h"
#include <thread>


using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

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
