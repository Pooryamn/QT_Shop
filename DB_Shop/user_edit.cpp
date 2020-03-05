#include "user_edit.h"
#include "ui_user_edit.h"

user_edit::user_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_edit)
{
    ui->setupUi(this);

    setup();
}

user_edit::~user_edit()
{
    delete ui;
}

void user_edit::setup(){
    ui->txt_user->setReadOnly(true);
    ui->txt_email->setReadOnly(true);
}
