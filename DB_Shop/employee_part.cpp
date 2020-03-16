#include "employee_part.h"
#include "ui_employee_part.h"

employee_part::employee_part(QWidget *parent,QString usrname) :
    QDialog(parent),
    ui(new Ui::employee_part)
{
    ui->setupUi(this);
    UserName = usrname;

    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    set_form();
    Setup();

    load_data(UserName);

    Search(ui->txt_search->text(),0);

}

employee_part::~employee_part()
{
    DB.Disconnect();
    delete ui;
}

void employee_part::on_btn_resizer_clicked()
{
    if(ui->btn_resizer->text() == "<"){
        this->setFixedSize(1000,720);
        ui->lbl_border->setGeometry(15,15,970,690);
        ui->btn_resizer->setText(">");
        ui->btn_resizer->setGeometry(975,315,15,75);
    }
    else {
        this->setFixedSize(1280,720);
        ui->lbl_border->setGeometry(15,15,1250,690);
        ui->btn_resizer->setText("<");
        ui->btn_resizer->setGeometry(1255,315,15,75);
    }
}

void employee_part::on_btn_newstock_clicked()
{
    delete model;
    DB.Disconnect();
    new_stock* stock = new new_stock(this);
    stock->setFixedSize(stock->width(),stock->height());
    stock->exec();
    DB.Connect();


    if(stock->new_supplier_called()){

        New_supplier* supplier = new New_supplier(this,0,0);
        supplier->setFixedSize(supplier->width(),supplier->height());
        DB.Disconnect();
        supplier->exec();

        new_stock* stock2 = new new_stock(this);
        stock2->setFixedSize(stock2->width(),stock2->height());
        DB.Disconnect();
        stock2->exec();
        DB.Connect();
    }
    Search(ui->txt_search->text(),0);
}

void employee_part::on_btn_ediprofile_clicked()
{
    delete model;
    user_edit* editor = new user_edit(this,UserName,2);
    editor->setFixedSize(editor->width(),editor->height());
    DB.Disconnect();
    editor->exec();
    DB.Connect();
    load_data(UserName);
    Search(ui->txt_search->text(),0);
}

void employee_part::on_btn_payment_clicked()
{
    delete model;
    user_payment* pay = new user_payment(this,UserName);
    pay->setFixedSize(pay->width(),pay->height());
    pay->exec();
    Search(ui->txt_search->text(),0);
}

void employee_part::on_btn_history_clicked()
{
    delete model;
    Shop_history* his = new Shop_history(this);
    his->setFixedSize(his->width(),his->height());
    his->exec();
    Search(ui->txt_search->text(),0);
}


void employee_part::set_form(){

    ui->txt_email->setReadOnly(true);
    ui->txt_username->setReadOnly(true);
    ui->txt_lastname->setReadOnly(true);
    ui->txt_firstname->setReadOnly(true);
    ui->pic_profile->setEnabled(true);
}

void employee_part::load_data(QString username){

    // get data from DB and set them in form:

    QString query_str;
    QSqlQuery query;

    query_str = "select firstname,lastname,"
                "email,attachments "
                "from employee "
                "where username = "
                "\'" + username +"\' ;";

    if(DB.Execute(query_str,query)){

        query.first();

        ui->txt_username->setText(username);
        ui->txt_firstname->setText(query.value(0).toString());
        ui->txt_lastname->setText(query.value(1).toString());
        ui->txt_email->setText(query.value(2).toString());


        QByteArray PIC = query.value(3).toByteArray();
        QPixmap pixx;
        pixx.loadFromData(PIC,nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_profile->width(),Qt::SmoothTransformation);
        ui->pic_profile->setPixmap(pixx);
    }
    else {
        qDebug() << "Error executing query";
        exit(0);
    }
}

void employee_part::on_btn_logoff_clicked()
{
    Widget* w = new Widget(0);
    w->setFixedSize(w->width(),w->height());
    w->setGeometry(500,200,w->width(),w->height());
    this->close();
    w->show();
}

void employee_part::Search(QString key, int Type){

    QString query_str;
    QSqlQuery query;

    if(Type == 0){
        // search by name}
        if(key.remove(" ").isEmpty()){
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products;";
        }
        else {

            query_str = "select \"Product ID\",\"Product name\" "
                        "from products where \"Product name\" like \'%" + key +"%\'";
        }
    }
    else {
        // serch by category
        if(key.remove(" ").isEmpty()){
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products;";
        }
        else{
            query_str = "select \"Product ID\",\"Product name\" "
                        "from products where category like \'%" + key +"%\'";

        }
    }
    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    model = new QSqlQueryModel(this);

    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Productname");

    ui->tbl_search->setModel(model);

    ui->tbl_search->setColumnWidth(0,50);
    ui->tbl_search->setColumnWidth(1,190);

    ui->tbl_search->setSelectionMode(QAbstractItemView::SingleSelection);


}



void employee_part::on_txt_search_textChanged(const QString &arg1)
{
    if(ui->radio_Name->isChecked()){
        Search(arg1,0);
    }
    else{
        Search(arg1,1);
    }
}

void employee_part::load_search_data(int ID){

    Setup();

    QString query_str;
    QSqlQuery query;

    query_str = "select * from products where \"Product ID\" = "+ QString::number(ID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    query.first();

    QString Pname = query.value(2).toString();
    QString Cname = find_company(query.value(1).toInt());
    QString Category = query.value(3).toString();
    QString UnitCost = query.value(4).toString();
    QString Stock = query.value(5).toString();
    QString Desc = query.value(6).toString();

    int Stk = Stock.toInt();

    if(Stk > 0){
        ui->lbl_avalablity->setText("Available");
        ui->lbl_avalablity->setStyleSheet("color: rgb(78, 154, 6);");
    }
    else if (Stk == 0){
        ui->lbl_avalablity->setText("Not Available");
        ui->lbl_avalablity->setStyleSheet("color: rgb(255, 0, 0);");
    }

    QString Html = "<h6>"
                    "<p style= \"color : #FF0000 \" ; >  Product Name : </p>"
                    "<p style= \"color : #1010FF \" ; > " + Pname +  " </p> "
                    "<p style= \"color : #FF0000 \" ; >  Company : </p>"
                    "<p style= \"color : #1010FF \" ; > " + Cname + " </p> "
                    "<p style= \"color : #FF0000 \" ; >  Category : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Category +  "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Cost : </p> "
                    "<p style= \"color : #1010FF \" ; > " + UnitCost + "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Stock : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Stock + "</p>"
                    "<br>"
                    "<p style= \"color : #FF0000 \" ; >  Description : </p> "
                    "<p style= \"color : #1010FF \" ; >" + Desc + "</p>"
                    "<br>"
                    "</h6>";

    ui->txt_description->setHtml(Html);

    // pics :
    query_str.clear();
    query.clear();

    query_str = "select * from product_pic where \"Product ID\" = " + QString::number(ID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return ;
    }

    for(int i = 0;i<6;i++){
        image[i].clear();
    }

    query.first();

    for (int i = 0;i<query.size();i++) {
        image[i] = query.value(2).toByteArray();
        query.next();
    }

    if(image[0].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[0],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_0->width(),Qt::SmoothTransformation);
        ui->pic_0->setPixmap(pixx);


        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_1->setPixmap(pixx);



    }

    if(image[1].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[1],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_2->setPixmap(pixx);
    }


    if(image[2].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[2],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_3->setPixmap(pixx);
    }


    if(image[3].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[3],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_4->setPixmap(pixx);
    }


    if(image[4].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[4],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_5->setPixmap(pixx);
    }


    if(image[5].isEmpty() == false){
        QPixmap pixx;
        pixx.loadFromData(image[5],nullptr,Qt::AutoColor);
        pixx = pixx.scaledToWidth(ui->pic_1->width(),Qt::SmoothTransformation);
        ui->pic_6->setPixmap(pixx);
    }

}

QString employee_part::find_company(int id){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company name\" from suppliers"
                " inner join products on suppliers.\"Supplier ID\" "
                "= products.\"Supplier ID\" "
                "where suppliers.\"Supplier ID\" = " + QString::number(id)+ ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return "";
    }

    query.first();

    return query.value(0).toString();
}



void employee_part::on_tbl_search_clicked(const QModelIndex &index)
{
    int id = ui->tbl_search->model()->index(index.row(),0).data().toInt();
    load_search_data(id);
}

void employee_part::Setup(){

    // Set Not found picture on mini pic1
    ui->pic_1->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));


    // Set Not found picture on mini pic2
    ui->pic_2->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic3
    ui->pic_3->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_4->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_5->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on mini pic2
    ui->pic_6->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(35,35,Qt::KeepAspectRatio));

    // Set Not found picture on Big pic
    ui->pic_0->setPixmap(QPixmap(QString::fromUtf8(":/Res/img/not_found.png")).scaled(200,200,Qt::KeepAspectRatio));

    //
    ui->txt_description->setReadOnly(true);

    ui->lbl_avalablity->setText("");

    ui->spin_stock->setMinimum(1);
}


void employee_part::on_btn_addstock_clicked()
{
    int addition_stock = ui->spin_stock->value();

    QModelIndex idx = ui->tbl_search->currentIndex();
    int id = ui->tbl_search->model()->index(idx.row(),0).data().toInt();

    QString query_str;
    QSqlQuery query;

    query_str = "update products set stock = stock + " + QString::number(addition_stock) +
                " where \"Product ID\" = " + QString::number(id) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return ;
    }
    QMessageBox::about(this,"successful","Done!");

    load_search_data(id);
}

void employee_part::on_radio_Name_clicked()
{
    Search(ui->txt_search->text(),0);
}

void employee_part::on_redio_Category_clicked()
{
    Search(ui->txt_search->text(),1);
}
