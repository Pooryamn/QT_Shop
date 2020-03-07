#include "master_signup.h"
#include "ui_master_signup.h"

Master_signup::Master_signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Master_signup)
{
    ui->setupUi(this);
}

Master_signup::~Master_signup()
{
    delete ui;
}
