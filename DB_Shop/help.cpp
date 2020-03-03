#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    ui->pic_programmer->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/programmer.png")).scaled(65,65,Qt::KeepAspectRatio));
    ui->pic_phone->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/Mobile.png")).scaled(50,50,Qt::KeepAspectRatio));
    ui->pic_email1->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/Email.png")).scaled(50,50,Qt::KeepAspectRatio));
    ui->pic_email2->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/Email.png")).scaled(50,50,Qt::KeepAspectRatio));
    ui->pic_telegram->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/Telegram.png")).scaled(65,65,Qt::KeepAspectRatio));
    ui->pic_git->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/Github.png")).scaled(60,60,Qt::KeepAspectRatio));

}

Help::~Help()
{
    delete ui;
}
