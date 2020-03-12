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

void user_part::on_btn_ediprofile_clicked()
{
    user_edit* editor = new user_edit(this);
    editor->setFixedSize(editor->width(),editor->height());
    editor->exec();
}

void user_part::on_btn_payment_clicked()
{
    user_payment* pay = new user_payment(this);
    pay->setFixedSize(pay->width(),pay->height());
    pay->exec();
}

void user_part::on_btn_history_clicked()
{
    Shop_history* his = new Shop_history(this);
    his->setFixedSize(his->width(),his->height());
    his->exec();
}

void user_part::on_btn_viewfavorite_clicked()
{
    favorites* fav = new favorites(this);
    fav->setFixedSize(fav->width(),fav->height());
    fav->exec();
}

void user_part::set_user(QString username){
    UserName = username;
}
