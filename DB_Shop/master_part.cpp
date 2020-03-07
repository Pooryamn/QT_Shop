#include "master_part.h"
#include "ui_master_part.h"

master_part::master_part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::master_part)
{
    ui->setupUi(this);
}

master_part::~master_part()
{
    delete ui;
}

void master_part::on_btn_resizer_clicked()
{
    if(ui->btn_resizer->text() == "<"){
        this->setFixedSize(1000,720);
        ui->lbl_border->setGeometry(15,15,970,690);
        ui->btn_resizer->setText(">");
        ui->btn_resizer->setGeometry(975,315,15,75);
    }
    else {
        this->setFixedSize(1280,720);
        ui->lbl_border->setGeometry(15,15,1250,690);
        ui->btn_resizer->setText("<");
        ui->btn_resizer->setGeometry(1255,315,15,75);
    }
}

void master_part::on_btn_newstock_clicked()
{
    new_stock* stock = new new_stock(this);
    stock->setFixedSize(stock->width(),stock->height());
    stock->exec();
}

void master_part::on_btn_ediprofile_clicked()
{
    user_edit* editor = new user_edit(this);
    editor->setFixedSize(editor->width(),editor->height());
    editor->exec();
}

void master_part::on_btn_payment_clicked()
{
    user_payment* pay = new user_payment(this);
    pay->setFixedSize(pay->width(),pay->height());
    pay->exec();
}

void master_part::on_btn_history_clicked()
{
    Shop_history* his = new Shop_history(this);
    his->setFixedSize(his->width(),his->height());
    his->exec();
}
