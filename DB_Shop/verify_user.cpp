#include "verify_user.h"
#include "ui_verify_user.h"

Verify_User::Verify_User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verify_User)
{
    ui->setupUi(this);
}

Verify_User::~Verify_User()
{
    delete ui;
}
