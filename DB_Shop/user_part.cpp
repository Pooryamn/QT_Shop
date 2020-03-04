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
