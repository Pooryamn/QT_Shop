#include "verify_employee.h"
#include "ui_verify_employee.h"

verify_employee::verify_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::verify_employee)
{
    ui->setupUi(this);
}

verify_employee::~verify_employee()
{
    delete ui;
}
