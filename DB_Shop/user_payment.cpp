#include "user_payment.h"
#include "ui_user_payment.h"

user_payment::user_payment(QWidget *parent,QString usrname) :
    QDialog(parent),
    ui(new Ui::user_payment)
{
    ui->setupUi(this);
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
}
