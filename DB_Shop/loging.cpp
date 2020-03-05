#include "loging.h"
#include "ui_loging.h"

Loging::Loging(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loging)
{
    ui->setupUi(this);
}

Loging::~Loging()
{
    delete ui;
}

void Loging::on_btn_cancel_clicked()
{
    this->close();
}

void Loging::on_btn_login_clicked()
{

}

void Loging::on_btn_forget_clicked()
{
    forget* forget_pass = new forget(this);
    forget_pass->exec();
}
