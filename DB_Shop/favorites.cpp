#include "favorites.h"
#include "ui_favorites.h"

favorites::favorites(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::favorites)
{
    ui->setupUi(this);
}

favorites::~favorites()
{
    delete ui;
}
