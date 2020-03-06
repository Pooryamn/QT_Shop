#include "gateway.h"
#include "ui_gateway.h"

gateway::gateway(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gateway)
{
    ui->setupUi(this);
}

gateway::~gateway()
{
    delete ui;
}
