#include "shop_history.h"
#include "ui_shop_history.h"

Shop_history::Shop_history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop_history)
{
    ui->setupUi(this);
}

Shop_history::~Shop_history()
{
    delete ui;
}
