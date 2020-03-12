#include "user_edit.h"
#include "ui_user_edit.h"

user_edit::user_edit(QWidget *parent,QString usrname,int type) :
    QDialog(parent),
    ui(new Ui::user_edit)
{
    ui->setupUi(this);

    Username = usrname;
    User_type = type;

    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    setup();

    load_data(Username,type);
}

user_edit::~user_edit()
{
    DB.Disconnect();
    delete ui;
}

void user_edit::setup(){


    Pass_Changed = false;

    ui->txt_user->setReadOnly(true);
    ui->txt_email->setReadOnly(true);
    ui->txt_name->setReadOnly(true);
    ui->txt_lastname->setReadOnly(true);

    // Mobile number lenght maximum is 20 and only digits
    ui->txt_mobile->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_mobile->setMaxLength(20);

    ui->txt_home->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_home->setMaxLength(15);

    ui->txt_city->setMaxLength(30);

    ui->txt_year->setMaxLength(4);
    ui->txt_year->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    ui->txt_month->setMaxLength(2);
    ui->txt_month->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    ui->txt_day->setMaxLength(2);
    ui->txt_day->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    ui->txt_post->setMaxLength(15);
    ui->txt_post->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

    // password maximum is 40 and it does not show
    ui->txt_pass->setMaxLength(40);
    ui->txt_pass->setEchoMode(QLineEdit::Password);

    // Comfrim password is 40 and does not show :
    ui->txt_comfrim->setMaxLength(40);
    ui->txt_comfrim->setEchoMode(QLineEdit::Password);

}

void user_edit::load_data(QString& username, int type){

    QSqlQuery query;
    QString query_str;


    if(type == 1){
        // search in customers
        query_str = "select firstname,lastname,email,"
                    "\"Phone number\",\"Mobile number\","
                    "address,city,\"Postal code\",birthdate,"
                    "attachments from customers "
                    "where username = "
                    "\'" + username + "\' ;";


    }
    else{
        // search in employee
        query_str = "select firstname,lastname,email,"
                    "\"Phone number\",\"Mobile number\","
                    "address,city,\"Postal code\",birthdate,"
                    "attachments from employee "
                    "where username = "
                    "\'" + username + "\' ;";
    }

    if(DB.Execute(query_str,query)){

        query.first();

        ui->txt_user->setText(username);
        ui->txt_name->setText(query.value(0).toString());
        ui->txt_lastname->setText(query.value(1).toString());
        ui->txt_email->setText(query.value(2).toString());
        ui->txt_home->setText(query.value(3).toString().remove("null"));
        ui->txt_mobile->setText(query.value(4).toString());
        ui->textEdit->setText(query.value(5).toString().remove("null"));
        ui->txt_city->setText(query.value(6).toString().remove("null"));
        ui->txt_post->setText(query.value(7).toString().remove("null"));

        QString in_birth = query.value(8).toString();
        QStringList birthd = in_birth.split("-");

        ui->txt_year->setText(birthd[0]);
        ui->txt_month->setText(birthd[1]);
        ui->txt_day->setText(birthd[2]);

        image = query.value(9).toByteArray();
        QPixmap pixx;
        pixx.loadFromData(image,nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_profile->width(),Qt::SmoothTransformation);
        ui->pic_profile->setPixmap(pixx);

    }
    else{

        qDebug() << "Cant execute query";
        exit(0);
    }
}

bool user_edit::check_inputs(){

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

    if(ui->txt_pass->text().remove(" ").isEmpty() == false){

        if(ui->txt_pass->text() != ui->txt_comfrim->text()){
            QMessageBox::warning(this,"Input Error",".:: Password isn't Confrim correctly!");
            return false;
        }
        Pass_Changed = true;
    }
    else{
        Pass_Changed = false;
    }
    return true;
}

void user_edit::on_btn_save_clicked()
{
    if(check_inputs()==false){
        return;
    }

    QString query_str;
    QSqlQuery query;

    if(Pass_Changed == true){

        query_str = "update account "
                    " set passwords = "
                    "\'" + ui->txt_pass->text() + "\' "
                    "where username = "
                    "\'" + Username +"\' ;";

        if(DB.Execute(query_str,query) == false){
            qDebug() << "Error execute query";
            exit(0);
        }
        query.clear();
        query_str.clear();
    }

    if(User_type == 1){
        // user
        query.prepare("update customers "
                      "set \"Mobile number\" = :MB ,"
                      "\"Phone number\" = :HM ,"
                      "birthdate = :BD ,"
                      "city = :CT ,"
                      "\"Postal code\" = :PC ,"
                      "address = :ADDD ,"
                      "attachments = :ATT "
                      "where username = "
                      "\'" + Username + "\' ;");

        query.bindValue(":MB",ui->txt_mobile->text());
        query.bindValue(":HM",ui->txt_home->text());
        query.bindValue(":BD",ui->txt_year->text()+ "-" + ui->txt_month->text() + "-" + ui->txt_day->text());
        query.bindValue(":CT",ui->txt_city->text());
        query.bindValue(":PC",ui->txt_post->text());
        query.bindValue(":ADDD",ui->textEdit->toPlainText());
        query.bindValue(":ATT",image);

    }
    else{
        // employee
        query.prepare("update employee "
                      "set \"Mobile number\" = :MB ,"
                      "\"Phone number\" = :HM ,"
                      "birthdate = :BD ,"
                      "city = :CT ,"
                      "\"Postal code\" = :PC ,"
                      "address = :ADDD ,"
                      "attachments = :ATT "
                      "where username = "
                      "\'" + Username + "\' ;");

        query.bindValue(":MB",ui->txt_mobile->text());
        query.bindValue(":HM",ui->txt_home->text());
        query.bindValue(":BD",ui->txt_year->text()+ "-" + ui->txt_month->text() + "-" + ui->txt_day->text());
        query.bindValue(":CT",ui->txt_city->text());
        query.bindValue(":PC",ui->txt_post->text());
        query.bindValue(":ADDD",ui->textEdit->toPlainText());
        query.bindValue(":ATT",image);
    }

    if(DB.Execute(query_str,query)){
        QMessageBox::about(this,"succsessful","Information Updated");
        this->close();
    }
    else{
        qDebug() << query.lastQuery() <<endl;
        qDebug() << query.lastError() << endl;
        return;
    }
}

void user_edit::on_btn_clear_clicked()
{
    image.clear();
    ui->pic_profile->clear();
}

void user_edit::on_btn_load_clicked()
{
    // clear old pic
    on_btn_clear_clicked();
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
}

void user_edit::on_btn_cansel_clicked()
{
    this->close();
}

void user_edit::on_btn_close_clicked()
{
    exit(0);
}
