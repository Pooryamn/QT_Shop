#include "employee_part.h"
#include "ui_employee_part.h"

employee_part::employee_part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee_part)
{
    ui->setupUi(this);
}

employee_part::~employee_part()
{
    delete ui;
}

void employee_part::on_btn_resizer_clicked()
{
    if(ui->btn_resizer->text() == "<"){
        this->setFixedSize(1000,720);
        ui->lbl_border->setGeometry(15,15,970,690);
        ui->btn_resizer->setText(">");
        ui->btn_resizer->setGeometry(975,315,15,75);
    }
    else {
        this->setFixedSize(1280,720);
        ui->lbl_border->setGeometry(15,15,1250,690);
        ui->btn_resizer->setText("<");
        ui->btn_resizer->setGeometry(1255,315,15,75);
    }
}
