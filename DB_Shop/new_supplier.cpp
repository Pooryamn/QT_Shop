#include "new_supplier.h"
#include "ui_new_supplier.h"

New_supplier::New_supplier(QWidget *parent,int T,int id) :
    QDialog(parent),
    ui(new Ui::New_supplier)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database connection error";
        exit(0);
    }

    Type = T; // 0 : new , 1 : edit

    ID = id;

    if(T == 1){
        load_data(ID);
        ui->btn_save->setVisible(false);
        ui->btn_clear->setVisible(false);
        ui->btn_choose->setVisible(false);
    }

}

New_supplier::~New_supplier()
{
    DB.Disconnect();
    delete ui;
}

bool New_supplier::check_input(){

    if(ui->txt_company->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"input error","Company name is empty");
        return false;
    }
    if(isValidSupplier(ui->txt_company->text())){
        QMessageBox::warning(this,"input error","Company already exists");
        return false;
    }

    if(ui->txt_email->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"input error","email is empty");
        return false;
    }

    if(ui->txt_type->text().remove(" ").isEmpty()){
        QMessageBox::warning(this,"input error","Company type is empty");
        return false;
    }

    return true;
}

void New_supplier::on_btn_clear_clicked()
{
    ui->pic->clear();
    image.clear();
}

void New_supplier::on_btn_choose_clicked()
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
    img = img.scaledToWidth(ui->pic->width(),Qt::SmoothTransformation);
    ui->pic->setPixmap(QPixmap::fromImage(img));

    // converting Qimage to QByteArray :
    QBuffer buffer(&image);
    buffer.open(QIODevice::WriteOnly);

    QPixmap::fromImage(img).save(&buffer,"PNG");

}

void New_supplier::on_btn_save_clicked()
{
    if(check_input() == false){
        return;
    }

    QString query_str;
    QSqlQuery query;

    if(Type == 0){

        query.prepare("insert into suppliers ("
                      "\"Company name\",email,phone,"
                      "\"Company Type\",attachments) values"
                      "(:Name,:EM,:PH,:Type,:ATT);");

        query.bindValue(":Name",ui->txt_company->text().toLower());
        query.bindValue(":EM",ui->txt_email->text());
        query.bindValue(":PH",ui->txt_phone->text());
        query.bindValue(":Type",ui->txt_type->text().toLower());
        query.bindValue(":ATT",image);
    }

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return;
    }
    qDebug() << query.lastQuery();
    QMessageBox::about(this,"successful","Done!");
    this->close();
}

bool New_supplier::isValidSupplier(QString name){

    QSqlQuery query;

    QString query_str = "select \"Supplier ID\" "
                        "from suppliers"
                        " where \"Company name\" ="
                        " \'" + name + "\';";

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
    return  false;
}

void New_supplier::load_data(int id){

    QString query_str;
    QSqlQuery query;

    query_str = "select * from suppliers where \"Supplier ID\" = " + QString::number(id) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return;
    }

    query.first();

    ui->txt_company->setText(query.value(1).toString());
    ui->txt_email->setText(query.value(2).toString());
    ui->txt_phone->setText(query.value(3).toString().remove("null"));
    ui->txt_type->setText(query.value(4).toString());

    image = query.value(5).toByteArray();

    QPixmap pixx;
    pixx.loadFromData(image,nullptr,Qt::AutoColor);
    pixx = pixx.scaledToWidth(ui->pic->width(),Qt::SmoothTransformation);
    ui->pic->setPixmap(pixx);

}
