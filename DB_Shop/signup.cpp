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

    // There is no profile_pic;
    on_btn_clear_clicked();
    profile_filled = false;

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

        // Send an email to employee :
        QString Email = ui->txt_email->text();
        QString Name = ui->txt_name->text() + " " + ui->txt_lastname->text();
        QString Subject = "P_Shop Verification Code";

        QString E_Code = RandStr();

        QString Body = "Dear " + Name + "\n"
                       "Your verification code is : " + E_Code ;


        if(Send_Email(Email,Name,Subject,Body) == false){
            QMessageBox::warning(this,"Email Sending Error","Fail to send Verification code\nCheck your email address and your internet connection");
            return;
        }

        Email = "Poorya.m.n.b@gmail.com";
        Subject = "P_Shop Master Verification Code";

        QString M_Code = RandStr();

        Body = "Dear Poorya Mohammadi\n" + Name +
               " wants to be a employee\n"
               "Information is : \n"
               "\tNational ID : " + ui->txt_national->text() + "\n"
               "\tMobile : " + ui->txt_mobile->text() + "\n"
               "\tEmail : " + ui->txt_email->text() + "\n"
                "===========================================================\n"
               "Your verification code is : " + M_Code ;

        if(Send_Email(Email,Name,Subject,Body) == false){
            QMessageBox::warning(this,"Email Sending Error","Fail to send Verification code\nCheck your email address and your internet connection");
            return;
        }

        verify_employee* emp = new verify_employee(this);
        emp->setFixedSize(emp->width(),emp->height());
        emp->SetPass(E_Code,M_Code);
        emp->exec();
        if(emp->get_status() == true){
            qDebug() << "ADD TO Database";
        }
        else {
            qDebug() << "NOOOOO";
        }
    }
    else{



        // Send an email to User :
        QString Email = ui->txt_email->text();
        QString Name = ui->txt_name->text() + " " + ui->txt_lastname->text();
        QString Subject = "P_Shop Verification Code";

        QString U_Code = RandStr();

        QString Body = "Dear " + Name + "\n"
                       "Your verification code is : " + U_Code ;


        if(Send_Email(Email,Name,Subject,Body) == false){
            QMessageBox::warning(this,"Email Sending Error","Fail to send Verification code\nCheck your email address and your internet connection");
            return;
        }



        Verify_User* user = new Verify_User(this);
        user->setFixedSize(user->width(),user->height());
        user->SetPass(U_Code);
        user->exec();


        // check if verification code is true
        if(user->get_status() == true){

            // Add a new user to software :

            // add user to accounts :
            if(add_to_accounts(0) == false){
                QMessageBox::warning(this,"Database Error","Error in : add to Accounts table");
                return;
            }

            // add user to customers

            QString Home = ui->txt_home->text().remove(" ");
            QString Birthdate;
            QString Address = ui->textEdit->toPlainText().remove(" ");
            QString City = ui->txt_city->text().remove(" ");
            QString Post = ui->txt_post->text();


            QString query;

            if(Home.isEmpty()){
                Home = "null";
            }

            if(Address.isEmpty()){
                Address = "null";
            }

            if(City.isEmpty()){
                City = "null";
            }

            if(Post.isEmpty()){
                Post = "null";
            }


            if(ui->txt_day->text().isEmpty()){
                Birthdate = "null";
            }
            else{
                Birthdate = ui->txt_year->text() + "-" + ui->txt_month->text() + "-" +ui->txt_day->text();
            }



            if(profile_filled == true){

                // Query with attachments

                qDebug() << "Imahe : \n" << image ;

                query = "insert into customers(firstname,lastname,email,"
                        "\"Phone number\",\"Mobile number\","
                        "address,city,\"Postal code\","
                        "birthdate,wallet,username,attachments)values("
                        "\'" + ui->txt_name->text() + "\' ,"
                        "\'" + ui->txt_lastname->text() + "\' ,"
                        "\'" + ui->txt_email->text() + "\' ,"
                        "\'" + Home + "\' ,"
                        "\'" + ui->txt_mobile->text() + "\' ,"
                        "\'" + Address + "\' ,"
                        "\'" + City + "\' ,"
                        "\'" + Post + "\' ,"
                        "\'" + Birthdate + "\' ,"
                        "0 ,"
                        "\'" + ui->txt_user->text() + "\' ,"
                        +image + ");";


            }
            else {

                // Query without attachments


                query = "insert into customers(firstname,lastname,email,"
                        "\"Phone number\",\"Mobile number\","
                        "address,city,\"Postal code\","
                        "birthdate,wallet,username,attachments)values("
                        "\'" + ui->txt_name->text() + "\' ,"
                        "\'" + ui->txt_lastname->text() + "\' ,"
                        "\'" + ui->txt_email->text() + "\' ,"
                        "\'" + Home + "\' ,"
                        "\'" + ui->txt_mobile->text() + "\' ,"
                        "\'" + Address + "\' ,"
                        "\'" + City + "\' ,"
                        "\'" + Post + "\' ,"
                        "\'" + Birthdate + "\' ,"
                        "0 ,"
                        "\'" + ui->txt_user->text() + "\' ,"
                        "null );";

            }

            query.replace("\'null\'","null");

            // Execute it :
            if(DB.Execute(query) == true){
                QMessageBox::about(this,"Successful","\t\tWelcome\n now you can loggin ");
            }
        }
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

    // converting Qimage to QByteArray :

    QBuffer buffer(&image);

    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer);



    profile_filled = true;
}

void SignUp::on_btn_clear_clicked()
{
    ui->pic_profile->clear();

    profile_filled = false;
}

bool SignUp::Send_Email(QString Email,QString Name,QString Subject,QString Body){

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);


    // We need to set the username (your email address) and the password

    smtp.setUser("poorya.shop0@gmail.com");
    smtp.setPassword("223843877");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("poorya.shop0@gmail.com", "Poorya Shop"));
    message.addRecipient(new EmailAddress(Email, Name));
    message.setSubject(Subject);

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText(Body);

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    smtp.connectToHost();
    smtp.login();

    if(smtp.sendMail(message)){
        smtp.quit();
        return true;
    }
    else{
        smtp.quit();
        return false;
    }
}

QString SignUp::RandStr(){
    QString Rnd;

    Rnd.resize(6);

    Rnd[0] = QChar('A' + char(qrand() % ('Z' - 'A')));

    Rnd[1] = QChar('0' + char(qrand() % ('9' - '0')));

    Rnd[2] = QChar('a' + char(qrand() % ('z' - 'a')));

    Rnd[3] = QChar('A' + char(qrand() % ('Z' - 'A')));

    Rnd[4] = QChar('a' + char(qrand() % ('z' - 'a')));

    Rnd[5] = QChar('0' + char(qrand() % ('9' - '0')));

    return Rnd;
}

bool SignUp::add_to_accounts(int type){

    QString query;
    query = "insert into account(username,\"Password\",\"Account type\")values("
            "\'" + ui->txt_user->text() + "\' ,"
            "\'" + ui->txt_pass->text() + "\' ,"
            + QString::number(type) + ");";

    if(DB.Execute(query) == false){
        return false;
    }
    return true;
}
