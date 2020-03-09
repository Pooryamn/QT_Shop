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

    if(ui->redio_employee->isChecked()){
        if(ui->txt_national->text().length() != 10 ){
            QMessageBox::warning(this,"Input Error",".:: Enter a valid National ID");
            return;
        }
    }

    if(check_inputs() == false){
        return;
    }

    if(ui->redio_employee->isChecked()){

        // Send Emails

        verify_employee* emp = new verify_employee(this);
        emp->setFixedSize(emp->width(),emp->height());
        emp->exec();
    }
    else{

        // send Email

        Verify_User* user = new Verify_User(this);
        user->setFixedSize(user->width(),user->height());
        user->exec();
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

bool SignUp::check_inputs(){

    // Firstname cant be empty
    if(ui->txt_name->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Firstname is empty!");
        return false;
    }

    // Lastname cant be empty
    if(ui->txt_lastname->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Lastname is empty!");
        return false;
    }

    // Email cant be empty and must contains "@" sign :
    if(ui->txt_email->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Email address is empty!");
        return false;
    }

    if(ui->txt_email->text().contains('@') == false){
        QMessageBox::warning(this,"Input Error",".:: Enter a valid email address!");
        return false;
    }

    // mobile length = 10
    if(ui->txt_mobile->text().length()<10){
        QMessageBox::warning(this,"Input Error",".:: Enter a valid Mobile number");
        return false;
    }

    // birthdate check :
    if((!ui->txt_year->text().isEmpty()) || (!ui->txt_month->text().isEmpty()) || (!ui->txt_day->text().isEmpty())){

        int tmp = ui->txt_month->text().toInt();
        if(tmp > 12 || tmp == 0){
            QMessageBox::warning(this,"Input Error",".:: Enter a valid Month");
            return false;
        }

        tmp = ui->txt_day->text().toInt();
        if(tmp > 31 || tmp == 0){
            QMessageBox::warning(this,"Input Error",".:: Enter a valid Day");
            return false;
        }
    }

    // Username cant be empty
    if(ui->txt_user->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Username is empty!");
        return false;
    }

    // Password and Comfrim password cant be empty and must be same
    if(ui->txt_pass->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Password is empty!");
        return false;
    }

    if(ui->txt_pass->text() != ui->txt_comfrim->text()){
        QMessageBox::warning(this,"Input Error",".:: Password isn't Confrim correctly!");
        return false;
    }
    return true;
}

void SignUp::on_btn_load_clicked()
{
    // load png , jpg files for image
    QString filename = QFileDialog::getOpenFileName(this,"Choose an Image...","","images (*.png *.jpg *.jpeg)");

    if(filename.isEmpty()){
        return;
    }

    QImage img;
    bool status = img.load(filename);

    if(status == false){
        QMessageBox::warning(this,"Input Error",".:: Image was corrupt");
        return;
    }
    img = img.scaledToWidth(ui->pic_profile->width(),Qt::SmoothTransformation);
    ui->pic_profile->setPixmap(QPixmap::fromImage(img));

    profile_filled = true;
}

void SignUp::on_btn_clear_clicked()
{
    ui->pic_profile->clear();

    profile_filled = false;
}
