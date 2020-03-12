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
}

void SignUp::on_btn_close_clicked()
{
    exit(0);
}

void SignUp::on_btn_cansel_clicked()
{
    DB.Disconnect();
    this->close();
    Widget* w = new Widget(0);
    w->setGeometry(500,200,w->width(),w->height());
    w->setFixedSize(w->width(),w->height());
    w->show();
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

        /*

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

        */

        verify_employee* emp = new verify_employee(this);
        emp->setFixedSize(emp->width(),emp->height());
        emp->SetPass("1","1");//E_Code,M_Code
        emp->exec();



        if(emp->get_status() == true){

            // Add a new user to software :

            // add user to accounts :
            if(add_to_accounts(1) == false){
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


            Birthdate = ui->txt_year->text() + "-" + ui->txt_month->text() + "-" +ui->txt_day->text();


            QSqlQuery q_query;

            if(profile_filled == true){

                // Query with attachments

               q_query.prepare("insert into employee(firstname,lastname,\"National ID\",email,"
                                "\"Phone number\",\"Mobile number\","
                                "address,city,\"Postal code\","
                                "birthdate,username,attachments)values("
                                " :Name ,"
                                " :LName ,"
                                " :NID ,"
                                " :EML ,"
                                " :HM ,"
                                " :MB ,"
                                " :ADDD ,"
                                " :CT ,"
                                " :PST ,"
                                " :BST ,"
                                " :USR ,"
                                " :IMG"
                                ");");
                q_query.bindValue(":Name",ui->txt_name->text());
                q_query.bindValue(":LName",ui->txt_lastname->text());
                q_query.bindValue(":NID",ui->txt_national->text());
                q_query.bindValue(":EML",ui->txt_email->text());
                q_query.bindValue(":HM",Home);
                q_query.bindValue(":MB",ui->txt_mobile->text());
                q_query.bindValue(":ADDD",Address);
                q_query.bindValue(":CT",City);
                q_query.bindValue(":PST",Post);
                q_query.bindValue(":BST",Birthdate);
                q_query.bindValue(":USR",ui->txt_user->text().toLower());
                q_query.bindValue(":IMG",image);
                query = "";
            }
            else {

                // Query without attachments

                query = "insert into employee(firstname,lastname,\"National ID\",email,"
                        "\"Phone number\",\"Mobile number\","
                        "address,city,\"Postal code\","
                        "birthdate,username,attachments)values("
                        "\'" + ui->txt_name->text() + "\' ,"
                        "\'" + ui->txt_lastname->text() + "\' ,"
                        "\'" + ui->txt_national->text() + "\' ,"
                        "\'" + ui->txt_email->text() + "\' ,"
                        "\'" + Home + "\' ,"
                        "\'" + ui->txt_mobile->text() + "\' ,"
                        "\'" + Address + "\' ,"
                        "\'" + City + "\' ,"
                        "\'" + Post + "\' ,"
                        "\'" + Birthdate + "\' ,"
                        "\'" + ui->txt_user->text().toLower() + "\' ,"
                        "null );";

                q_query.clear();

            }

            query.replace("\'null\'","null");

            // Execute it :

            if(DB.Execute(query,q_query) == true){

                QMessageBox::about(this,"Successful","       Welcome\n now you can login ");
                on_btn_cansel_clicked();
            }
            else{
                QMessageBox::warning(this,"Faild","Cant write data to database.\nTry again");
                qDebug() << q_query.lastQuery();
                qDebug() << q_query.lastError();
                return;
            }
        }

    }
    else{

        /*

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

        */

        Verify_User* user = new Verify_User(this);
        user->setFixedSize(user->width(),user->height());
        user->SetPass("1"); //U_Code
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


            Birthdate = ui->txt_year->text() + "-" + ui->txt_month->text() + "-" +ui->txt_day->text();



            QSqlQuery q_query;

            if(profile_filled == true){

                // Query with attachments

               q_query.prepare("insert into customers(firstname,lastname,email,"
                                "\"Phone number\",\"Mobile number\","
                                "address,city,\"Postal code\","
                                "birthdate,wallet,username,attachments)values("
                                " :Name ,"
                                " :LName ,"
                                " :EML ,"
                                " :HM ,"
                                " :MB ,"
                                " :ADDD ,"
                                " :CT ,"
                                " :PST ,"
                                " :BST ,"
                                "0 ,"
                                " :USR ,"
                                " :IMG"
                                ");");
                q_query.bindValue(":Name",ui->txt_name->text());
                q_query.bindValue(":LName",ui->txt_lastname->text());
                q_query.bindValue(":EML",ui->txt_email->text());
                q_query.bindValue(":HM",Home);
                q_query.bindValue(":MB",ui->txt_mobile->text());
                q_query.bindValue(":ADDD",Address);
                q_query.bindValue(":CT",City);
                q_query.bindValue(":PST",Post);
                q_query.bindValue(":BST",Birthdate);
                q_query.bindValue(":USR",ui->txt_user->text().toLower());
                q_query.bindValue(":IMG",image);
                query = "";



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
                        "\'" + ui->txt_user->text().toLower() + "\' ,"
                        "null );";

                q_query.clear();

            }

            query.replace("\'null\'","null");

            // Execute it :

            if(DB.Execute(query,q_query) == true){

                QMessageBox::about(this,"Successful","       Welcome\n now you can login ");
                on_btn_cansel_clicked();
            }
            else{
                QMessageBox::warning(this,"Faild","Cant write data to database.\nTry again");
                qDebug() << q_query.lastQuery();
                qDebug() << q_query.lastError();
                return;
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
    if((ui->txt_year->text().isEmpty()) || (ui->txt_month->text().isEmpty()) || (ui->txt_day->text().isEmpty())){
        QMessageBox::warning(this,"Input Error",".:: Birthdate is empty");
        return false;
    }
    else{

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

        tmp = ui->txt_year->text().toInt();
        if(tmp<1000 || tmp>1400){
            QMessageBox::warning(this,"Input Error",".:: Enter a valid Year");
            return false;
        }
    }

    // Username cant be empty and username cant besame with others
    if(ui->txt_user->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"Input Error",".:: Username is empty!");
        return false;
    }

    QSqlQuery query;
    QString query_str = "select username"
                        "from account"
                        " where username = "
                        "\'" + ui->txt_user->text().toLower()+"\' ;";

    if(DB.Execute(query_str,query)){
        if(query.isNull(0) == false){
            QMessageBox::warning(this,"Input Error",".:: This username already exists");
            return false;
        }
    }
    else{
        qDebug() << "Some thin wrong in select query" << endl;
        qDebug() << query.lastQuery() << endl;
        qDebug() << query.lastError() << endl;
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

    QPixmap::fromImage(img).save(&buffer,"PNG");



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
            "\'" + ui->txt_user->text().toLower() + "\' ,"
            "\'" + ui->txt_pass->text() + "\' ,"
            + QString::number(type) + ");";

    QSqlQuery q_query;
    if(DB.Execute(query,q_query) == false){
        return false;
    }
    return true;
}
