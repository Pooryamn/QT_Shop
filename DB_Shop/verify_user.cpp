#include "verify_user.h"
#include "ui_verify_user.h"

Verify_User::Verify_User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verify_User)
{
    ui->setupUi(this);
    Status = false;
}

Verify_User::~Verify_User()
{
    delete ui;
}

void Verify_User::SetPass(QString Usr){
    User = Usr;
}

bool Verify_User::get_status(){
    return Status;
}
void Verify_User::on_btn_edit_clicked()
{
    this->close();
}

void Verify_User::on_btn_verify_clicked()
{
    if(ui->txt_verifyCode->text() == User){
        Status = true;
        this->close();
    }
    else{
        Status = false;
        QMessageBox::warning(this,"Wrong Codes","Codes was not valid");
        return;
    }
}
