#include "user_edit.h"
#include "ui_user_edit.h"

user_edit::user_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_edit)
{
    ui->setupUi(this);
}

user_edit::~user_edit()
{
    delete ui;
}
