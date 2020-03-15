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
    //model = new QSqlQueryModel;
    Search(ui->txt_search->text(),0);


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
}

void employee_part::on_btn_ediprofile_clicked()
{
    user_edit* editor = new user_edit(this,UserName,2);
    editor->setFixedSize(editor->width(),editor->height());
    DB.Disconnect();
    editor->exec();
    DB.Connect();
    load_data(UserName);
}

void employee_part::on_btn_payment_clicked()
{
    user_payment* pay = new user_payment(this,UserName);
    pay->setFixedSize(pay->width(),pay->height());
    pay->exec();
}

void employee_part::on_btn_history_clicked()
{
    Shop_history* his = new Shop_history(this);
    his->setFixedSize(his->width(),his->height());
    his->exec();
}


void employee_part::set_form(){

    ui->txt_email->setDisabled(true);
    ui->txt_username->setDisabled(true);
    ui->txt_lastname->setDisabled(true);
    ui->txt_firstname->setDisabled(true);
    ui->pic_profile->setDisabled(true);
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
