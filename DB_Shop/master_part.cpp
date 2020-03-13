#include "master_part.h"
#include "ui_master_part.h"

master_part::master_part(QWidget *parent,QString usrname) :
    QDialog(parent),
    ui(new Ui::master_part)
{
    ui->setupUi(this);

    UserName = usrname;

    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    set_form();

    load_data(UserName);
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
    user_edit* editor = new user_edit(this,UserName,3);
    editor->setFixedSize(editor->width(),editor->height());
    DB.Disconnect();
    editor->exec();
    DB.Connect();
    load_data(UserName);
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

void master_part::on_btn_viewuser_clicked()
{
    Users* users = new Users(this);
    users->setFixedSize(users->width(),users->height());
    DB.Disconnect();
    users->exec();
    DB.Connect();
}

void master_part::on_btn_addmaster_clicked()
{
    Master_signup* master = new Master_signup(this);
    master->setFixedSize(master->width(),master->height());
    master->exec();
}

void master_part::on_btn_supplier_clicked()
{
    Suppliers* supply = new Suppliers(this);
    supply->setFixedSize(supply->width(),supply->height());
    supply->exec();
}

void master_part::set_form(){

    ui->txt_email->setDisabled(true);
    ui->txt_username->setDisabled(true);
    ui->txt_lastname->setDisabled(true);
    ui->txt_firstname->setDisabled(true);
    ui->pic_profile->setDisabled(true);
    ui->pic_profile->setEnabled(true);
}

void master_part::load_data(QString username){

    // get data from DB and set them in form:

    QString query_str;
    QSqlQuery query;

    query_str = "select firstname,lastname,"
                "email,attachments "
                "from employee "
                "where username = "
                "\'" + username +"\' ;";

    if(DB.Execute(query_str,query)){

        query.first();

        ui->txt_username->setText(username);
        ui->txt_firstname->setText(query.value(0).toString());
        ui->txt_lastname->setText(query.value(1).toString());
        ui->txt_email->setText(query.value(2).toString());


        QByteArray PIC = query.value(3).toByteArray();
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



void master_part::on_btn_logoff_clicked()
{
    Widget* w = new Widget(0);
    w->setFixedSize(w->width(),w->height());
    w->setGeometry(500,200,w->width(),w->height());
    this->close();
    w->show();
}
