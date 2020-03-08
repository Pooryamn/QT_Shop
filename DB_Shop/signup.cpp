#include "signup.h"
#include "ui_signup.h"
#include <QDebug>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    // Connect to the database :
    Connect_DB();

    // disable natioal id for normal user :
    ui->txt_national->setVisible(false);
    ui->lbl_national->setVisible(false);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_SignUp_finished(int result)
{
    Widget *w = new Widget(0);
    w->setGeometry(500,200,w->width(),w->height());
    w->show();
}

void SignUp::on_btn_close_clicked()
{
    exit(0);
}

void SignUp::on_btn_cansel_clicked()
{
    this->close();
}

void SignUp::on_radio_user_clicked()
{
    // disable natioal id for normal user :
    ui->txt_national->setVisible(false);
    ui->lbl_national->setVisible(false);
    ui->txt_national->setText("");
}

void SignUp::on_redio_employee_clicked()
{
    // enable natioal id for super user :
    ui->txt_national->setVisible(true);
    ui->lbl_national->setVisible(true);
}

void SignUp::Connect_DB(){

    QSqlDatabase DB = QSqlDatabase::addDatabase("PSQL"); // it is Postgresql Driver
    DB.setHostName("localhost");
    DB.setDatabaseName("P_Shop");
    DB.setPort(5432);
    DB.setUserName("postgres");
    DB.setPassword("223843877");
    bool status = DB.open();

    if (DB.open() == true){
        qDebug() << "Connected to Database";
    }
    else {
        /*

         ALGORITHM :

            First find the problem
            If Problem is Driver so tell the user to install it
            If Problem is Not existing Database so create it
        */

        // find problem :
        QString error = DB.lastError().text();

        // if it has Driver problem :
        if(error.contains("Driver")){
            QMessageBox::warning(this,"Database Error","Postgresql driver(QPSQL) not found !");
        }

    }
}

void SignUp::on_btn_verify_clicked()
{
    // check every thing is ok

    if(ui->radio_user->isChecked()){
        Verify_User *v_user = new Verify_User(this);
        v_user->setFixedSize(v_user->width(),v_user->height());
        v_user->exec();
    }
    else{
        verify_employee *v_employee = new verify_employee(this);
        v_employee->setFixedSize(v_employee->width(),v_employee->height());
        v_employee->exec();
    }
}
