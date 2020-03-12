#include "forget.h"
#include "ui_forget.h"

forget::forget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Cant connect to DB";
        exit(0);
    }


}

forget::~forget()
{
    DB.Disconnect();
    delete ui;
}

void forget::on_btn_cancel_clicked()
{
    this->close();
}


void forget::on_btn_recover_clicked()
{
    if(ui->txt_user->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"input error","Username is empty");
        return;
    }
    if(is_valid_User()){
        QString password = find_password(ui->txt_user->text().toLower(),Type);
        QString email = find_email(ui->txt_user->text().toLower(),Type);
        QString Body = "Dear " + ui->txt_user->text().toLower() + "\n"
                       "Your Password is : " + password + "\n _____________";

        if(Send_Email(email,ui->txt_user->text().toLower(),"Recover Password", Body) == true){
            QMessageBox::about(this,"Email Sent","Check your inbox");
            this->close();
        }
        else{
            QMessageBox::warning(this,"Email Error","Cant Send email\ncheck your internet connection");
            return;
        }
    }
    else {
        QMessageBox::warning(this,"Information error","Username does not exists");
    }
}

bool forget::is_valid_User(){

    QSqlQuery query;

    QString query_str = "select username"
                        " from account"
                        " where username = "
                        "\'" + ui->txt_user->text().toLower()+"\' ;";

    if(DB.Execute(query_str,query)){

        query.first();

        if(query.value(0).toString().isEmpty() == true){
            return false;
        }
        else{
            return true;
        }
    }
    else {
        qDebug() << "Error in executing select query";
    }
}

QString forget::find_password(QString username, int &type){

    QSqlQuery query;
    QString query_str;

    query_str ="select passwords,\"Account type\" "
                "from account "
                "where username = "
                "\'" + username + "\' ;";

    if(DB.Execute(query_str,query)){
        query.first();

        type = query.value(1).toInt();

        return query.value(0).toString();

    }
    else{
        qDebug() << "Cant execute query";
        exit(0);
    }
}

QString forget::find_email(QString username, int type){

    QSqlQuery query;
    QString query_str;


    if(type == 1){
        // search in customers
        query_str = "select email "
                    "from customers "
                    "where username = "
                    "\'" + username + "\' ;";
    }
    else{
        // search in employee
        query_str = "select email "
                    "from employee "
                    "where username = "
                    "\'" + username + "\' ;";
    }

    if(DB.Execute(query_str,query)){

        query.first();

        return query.value(0).toString();
    }
    else{

        qDebug() << "Cant execute query";
        exit(0);
    }
}

bool forget::Send_Email(QString Email,QString Name,QString Subject,QString Body){

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


