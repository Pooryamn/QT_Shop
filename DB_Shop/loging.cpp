#include "loging.h"
#include "ui_loging.h"


Loging::Loging(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loging)
{
    ui->setupUi(this);
    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }
    User_type = 0;
}

Loging::~Loging()
{
    DB.Disconnect();
    delete ui;
}

void Loging::on_btn_cancel_clicked()
{
    this->close();
}

void Loging::on_btn_login_clicked()
{
    if(check_inputs() == false){
        return ;
    }

    if(check_information() == false){
        return;
    }

    this->close();
}

void Loging::on_btn_forget_clicked()
{
    forget* forget_pass = new forget(this);
    forget_pass->exec();
}

void Loging::connect_to_db(){

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database Connection error";
        exit(0);
    }
}

void Loging::on_txt_User_editingFinished()
{
    QString tmp = ui->txt_User->text().remove(" ");
    ui->txt_User->setText(tmp);
}

bool Loging::check_inputs(){

    if(ui->txt_User->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"input Error","Username is epmty");
        return false;
    }

    if(ui->txt_password->text().isEmpty()){
        QMessageBox::warning(this,"input Error","Password is epmty");
        return false;
    }
    return true;
}

bool Loging::check_information(){

    QSqlQuery query;
    QString query_str;

    query_str = "select \"Account type\" "
                "from account "
                "where "
                "username = \'" + ui->txt_User->text().toLower() + "\' "
                " and passwords = \'" + ui->txt_password->text() + "\' ;" ;

    if(DB.Execute(query_str,query) ==false){
        qDebug() <<query.lastError();
    }

    query.first();

    int type = query.value(0).toInt();

    if(type == 0){
        QMessageBox::warning(this,"Information Error","invalid Username or Password!");
        return false;
    }

    User_type = type;

    return true;
}

int Loging::get_type(){
    return User_type;
}

QString Loging::get_user(){
    return ui->txt_User->text();
}

