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

void Master_signup::on_btn_verify_clicked()
{
    verify_employee *v_employee = new verify_employee(this);
    v_employee->setFixedSize(v_employee->width(),v_employee->height());
    v_employee->exec();
}
