#include "user_payment.h"
#include "ui_user_payment.h"

user_payment::user_payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_payment)
{
    ui->setupUi(this);
}

user_payment::~user_payment()
{
    delete ui;
}
