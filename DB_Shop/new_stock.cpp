#include "new_stock.h"
#include "ui_new_stock.h"

new_stock::new_stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_stock)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database connection error";
        exit(0);
    }

    supplier_called = false;

    set_input_method();

    load_suppliers();

}

new_stock::~new_stock()
{
    delete model;
    DB.Disconnect();
    delete ui;
}

void new_stock::on_btn_addsupplier_clicked()
{
    supplier_called = true;

    this->close();

    /*
    New_supplier* supplier = new New_supplier(this,0,0);
    supplier->setFixedSize(supplier->width(),supplier->height());
    DB.Disconnect();
    supplier->exec();
    DB.Connect();
    */
}

void new_stock::load_suppliers(){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company name\" from suppliers";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return;
    }

    model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"Company name");

    ui->tbl_supplier->setModel(model);

    ui->tbl_supplier->setColumnWidth(0,180);

    ui->tbl_supplier->setSelectionMode(QAbstractItemView::SingleSelection);
}


bool new_stock::new_supplier_called(){
    return supplier_called;
}

void new_stock::set_input_method(){

    ui->txt_cost->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_stock->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

}

bool new_stock::check_inputs(){

    QItemSelectionModel *select = ui->tbl_supplier->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input Error","First select a supplier or add new one");
        return false;
    }

    if(ui->txt_name->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Stock name");
        return false;
    }

    if(isValidProduct(SupplierID,ui->txt_name->text().remove(" "))){
        QMessageBox::warning(this,"Input Error","this product already exist with this supplier");
        return false;
    }

    if(ui->txt_category->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Category");
        return false;
    }

    if(ui->txt_cost->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Cost value");
        return false;
    }

    if(ui->txt_stock->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Stock number");
        return false;
    }

    if(ui->textEdit->toPlainText().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Description");
        return false;
    }

    return true;
}


void new_stock::on_tbl_supplier_clicked(const QModelIndex &index)
{
    QString Category = get_category(index.data().toString());

    ui->txt_category->setText(Category);

}


QString new_stock::get_category(QString Company){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company Type\",\"Supplier ID\" from suppliers where \"Company name\" = \'" + Company + "\';";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return "";
    }

    query.first();

    SupplierID = query.value(1).toInt();
    return query.value(0).toString();
}

void new_stock::on_btn_choose1_clicked()
{
    if(ui->btn_choose1->text() == "Choose ..."){

        image[0].clear();

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
        img = img.scaled(ui->pic_1->width(),ui->pic_1->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_1->setPixmap(QPixmap::fromImage(img));

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[0]);
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose1->setText("Clear");

    }
    else{

        image[0].clear();
        ui->pic_1->clear();
        ui->btn_choose1->setText("Choose ...");

    }
}

void new_stock::on_btn_choose2_clicked()
{
    if(ui->btn_choose2->text() == "Choose ..."){ //

        image[1].clear(); //

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
        img = img.scaled(ui->pic_2->width(),ui->pic_2->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_2->setPixmap(QPixmap::fromImage(img));//

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[1]);//
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose2->setText("Clear");//

    }
    else{

        image[1].clear();//
        ui->pic_2->clear();//
        ui->btn_choose2->setText("Choose ...");//

    }
}

void new_stock::on_btn_choose3_clicked()
{
    if(ui->btn_choose3->text() == "Choose ..."){ //

        image[2].clear(); //

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
        img = img.scaled(ui->pic_3->width(),ui->pic_3->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_3->setPixmap(QPixmap::fromImage(img));//

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[2]);//
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose3->setText("Clear");//

    }
    else{

        image[2].clear();//
        ui->pic_3->clear();//
        ui->btn_choose3->setText("Choose ...");//

    }
}

void new_stock::on_btn_choose4_clicked()
{
    if(ui->btn_choose4->text() == "Choose ..."){ //

        image[3].clear(); //

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
        img = img.scaled(ui->pic_4->width(),ui->pic_4->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_4->setPixmap(QPixmap::fromImage(img));//

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[3]);//
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose4->setText("Clear");//

    }
    else{

        image[3].clear();//
        ui->pic_4->clear();//
        ui->btn_choose4->setText("Choose ...");//

    }
}

void new_stock::on_btn_choose5_clicked()
{
    if(ui->btn_choose5->text() == "Choose ..."){ //

        image[4].clear(); //

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
        img = img.scaled(ui->pic_5->width(),ui->pic_5->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_5->setPixmap(QPixmap::fromImage(img));//

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[4]);//
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose5->setText("Clear");//

    }
    else{

        image[4].clear();//
        ui->pic_5->clear();//
        ui->btn_choose5->setText("Choose ...");//

    }
}

void new_stock::on_btn_choose6_clicked()
{
    if(ui->btn_choose6->text() == "Choose ..."){ //

        image[5].clear(); //

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

        img = img.scaled(ui->pic_6->width(),ui->pic_6->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->pic_6->setPixmap(QPixmap::fromImage(img));//

        // converting Qimage to QByteArray :
        QBuffer buffer(&image[5]);//
        buffer.open(QIODevice::WriteOnly);

        QPixmap::fromImage(img).save(&buffer,"PNG");


        ui->btn_choose6->setText("Clear");//

    }
    else{

        image[5].clear();//
        ui->pic_6->clear();//
        ui->btn_choose6->setText("Choose ...");//

    }
}

void new_stock::on_btn_addstock_clicked()
{
    if(check_inputs() == false){
        return;
    }

    delete model;

    // add data to stocks :
    QSqlQuery query;
    QString query_str;

    query.prepare( "insert into products (\"Supplier ID\",\"Product name\","
                "category,\"Unit cost\",stock,\"Description\")"
                "values(:SID,:PN,:CAT,:COST,:ST,:DES);");

    query.bindValue(":SID",SupplierID);
    query.bindValue(":PN",ui->txt_name->text().toLower());
    query.bindValue(":CAT",ui->txt_category->text().toLower());
    query.bindValue(":COST",ui->txt_cost->text().toInt());
    query.bindValue(":ST",ui->txt_stock->text().toInt());
    query.bindValue(":DES",ui->textEdit->toPlainText());

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return ;
    }

    query.clear();

    query_str = "select \"Product ID\" "
                "from products where "
                "\"Supplier ID\" = "
                + QString::number(SupplierID) +
                " and \"Product name\" = "
                "\'" + ui->txt_name->text().toLower() + "\';";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return ;
    }

    query.first();

    ProductID = query.value(0).toInt();

    query.clear();
    query_str.clear();

    // add pictures :
    if(image[0].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[0]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }

    }
    if(image[1].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[1]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }
    }
    if(image[2].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[2]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }
    }
    if(image[3].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[3]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }
    }
    if(image[4].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[4]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }
    }
    if(image[5].isEmpty() == false){
        query.prepare("insert into product_pic(\"Product ID\","
                      "attachments) values(:PID,:ATT);");

        query.bindValue(":PID",ProductID);
        query.bindValue(":ATT",image[5]);

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << query.lastError();
            return ;
        }
    }

    this->close();
}

bool new_stock::isValidProduct(int SuppID, QString PName){

    QSqlQuery query;

    QString query_str ;

    query_str = "select \"Product ID\" "
                "from products where"
                "\"Supplier ID\" = "
                + QString::number(SuppID) +
                " and \"Product name\" = "
                "\'" + PName + "\';";

    if(DB.Execute(query_str,query)){

        query.first();

        if(query.value(0).toInt() == 0){
            return false;
        }
        else{
            return true;
        }
    }
    else {
        qDebug() << "Error in executing select query";
    }
    return false;

}
