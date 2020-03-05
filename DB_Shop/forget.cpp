#include "forget.h"
#include "ui_forget.h"

forget::forget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget)
{
    ui->setupUi(this);
}

forget::~forget()
{
    delete ui;
    ui->txt_user->setFocus();
}

void forget::on_btn_cancel_clicked()
{
    this->close();
}
