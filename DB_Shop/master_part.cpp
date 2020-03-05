#include "master_part.h"
#include "ui_master_part.h"

master_part::master_part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::master_part)
{
    ui->setupUi(this);
}

master_part::~master_part()
{
    delete ui;
}
