#include "user_part.h"
#include "ui_user_part.h"

user_part::user_part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_part)
{
    ui->setupUi(this);
}

user_part::~user_part()
{
    delete ui;
}

void user_part::on_btn_resizer_clicked()
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

void user_part::on_btn_Cart_clicked()
{
    Cart* cart = new Cart(this);
    cart->setFixedSize(cart->width(),cart->height());
    cart->exec();
}
