#include "signup.h"
#include "ui_signup.h"
#include <QDebug>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    // Connect to database
    if(DB.Connect()!=0){
        qDebug() << "Database Connection Error!";
        exit(0);
    };

    // set objects on ui to take suitable inputs :
    set_input_methods();

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

void SignUp::set_input_methods(){

    // national ID is only digits and its lenght is 10 :
    ui->txt_national->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_national->setMaxLength(10);

    // Firstname and Lastname is maximum 50 letters :
    ui->txt_name->setMaxLength(50);
    ui->txt_lastname->setMaxLength(50);

    // Email lenght maximum is 70
    ui->txt_email->setMaxLength(70);

    // Mobile number lenght maximum is 20 and only digits
    ui->txt_mobile->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_mobile->setMaxLength(20);

    // Phone is only digit and maximum lenght is 15
    ui->txt_home->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_home->setMaxLength(15);

    // city maximum lenght is 30
    ui->txt_city->setMaxLength(30);

    // Username maximum lenght is 30
    ui->txt_user->setMaxLength(30);

    // Year = 4 digits , Month = 2 digits , day = 2 digits
    ui->txt_year->setMaxLength(4);
    ui->txt_year->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    ui->txt_month->setMaxLength(2);
    ui->txt_month->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    ui->txt_day->setMaxLength(2);
    ui->txt_day->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));


    // Postal code is 15 digits
    ui->txt_post->setMaxLength(15);
    ui->txt_post->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    // password maximum is 40 and it does not show
    ui->txt_pass->setMaxLength(40);
    ui->txt_pass->setEchoMode(QLineEdit::Password);

    // Comfrim password is 40 and does not show :
    ui->txt_comfrim->setMaxLength(40);
    ui->txt_comfrim->setEchoMode(QLineEdit::Password);

}
