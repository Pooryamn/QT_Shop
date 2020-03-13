#include "gateway.h"
#include "ui_gateway.h"

gateway::gateway(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gateway)
{
    ui->setupUi(this);

    Ammount = 0;

    set_input_method();
}

gateway::~gateway()
{
    delete ui;
}

void gateway::set_input_method(){

    ui->txt_amount->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
}

void gateway::on_btn_cancel_clicked()
{
    this->close();
}

void gateway::on_btn_pay_clicked()
{
    if(ui->txt_amount->text().isEmpty()){
        QMessageBox::warning(this,"Input error","Ammount is empty");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Confrim","Are you sure?");

    if(reply == QMessageBox::Yes){
        Ammount = ui->txt_amount->text().toInt();
        this->close();
    }
}
