#include "verify_employee.h"
#include "ui_verify_employee.h"

verify_employee::verify_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::verify_employee)
{
    ui->setupUi(this);
    status = false;
}

verify_employee::~verify_employee()
{
    delete ui;
}

void verify_employee::SetPass(QString emp,QString mas){
    Employee = emp;
    Master = mas;
}

void verify_employee::on_btn_edit_clicked()
{
    this->close();
}

void verify_employee::on_btn_verify_clicked()
{
    if((ui->txt_verifyCode->text() == Employee) && (ui->txt_mastercode->text() == Master)){
        status = true;
    }
    else {
        status = false;
    }
}

bool verify_employee::get_status(){
    return status;
}
