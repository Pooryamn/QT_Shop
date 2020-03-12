#include "user_part.h"
#include "ui_user_part.h"

user_part::user_part(QWidget *parent,QString usr) :
    QDialog(parent),
    ui(new Ui::user_part)
{
    ui->setupUi(this);
    UserName = usr;
    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    set_form();

    load_data(UserName);

}

user_part::~user_part()
{
    DB.Disconnect();
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
    user_edit* editor = new user_edit(this,UserName,1);
    editor->setFixedSize(editor->width(),editor->height());
    DB.Disconnect();
    editor->exec();
    DB.Connect();
    load_data(UserName);

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


void user_part::load_data(QString username){

    // get data from DB and set them in form:

    QString query_str;
    QSqlQuery query;

    query_str = "select firstname,lastname,"
                "email,wallet,attachments "
                "from customers "
                "where username = "
                "\'" + username +"\' ;";

    if(DB.Execute(query_str,query)){

        query.first();

        ui->txt_username->setText(username);
        ui->txt_firstname->setText(query.value(0).toString());
        ui->txt_lastname->setText(query.value(1).toString());
        ui->txt_email->setText(query.value(2).toString());
        ui->txt_wallet->setText(query.value(3).toString());


        QByteArray PIC = query.value(4).toByteArray();
        QPixmap pixx;
        pixx.loadFromData(PIC,nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_profile->width(),Qt::SmoothTransformation);
        ui->pic_profile->setPixmap(pixx);
    }
    else {
        qDebug() << "Error executing query";
        exit(0);
    }
}

void user_part::set_form(){

    ui->txt_email->setDisabled(true);
    ui->txt_wallet->setDisabled(true);
    ui->txt_username->setDisabled(true);
    ui->txt_lastname->setDisabled(true);
    ui->txt_firstname->setDisabled(true);
    ui->pic_profile->setDisabled(true);
    ui->pic_profile->setEnabled(true);
}

void user_part::on_btn_logoff_clicked()
{
    Widget* w = new Widget(0);
    w->setFixedSize(w->width(),w->height());
    w->setGeometry(500,200,w->width(),w->height());
    this->close();
    w->show();
}
