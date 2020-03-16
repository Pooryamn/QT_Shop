#include "user_part.h"
#include "ui_user_part.h"

user_part::user_part(QWidget *parent,QString usr) :
    QDialog(parent),
    ui(new Ui::user_part)
{
    ui->setupUi(this);
    UserName = usr;
    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    set_form();
    Setup();

    load_data(UserName);

    Search(ui->txt_search->text(),0);

    isFavorite(2,3);
    isFavorite(16,5);
}

user_part::~user_part()
{
    DB.Disconnect();
    delete ui;
}

void user_part::on_btn_resizer_clicked()
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

void user_part::on_btn_Cart_clicked()
{
    delete model;
    Cart* cart = new Cart(this);
    cart->setFixedSize(cart->width(),cart->height());
    cart->exec();
    Search(ui->txt_search->text(),0);
}

void user_part::on_btn_ediprofile_clicked()
{
    delete model;
    user_edit* editor = new user_edit(this,UserName,1);
    editor->setFixedSize(editor->width(),editor->height());
    DB.Disconnect();
    editor->exec();
    DB.Connect();
    load_data(UserName);
    Search(ui->txt_search->text(),0);

}

void user_part::on_btn_payment_clicked()
{
    delete model;
    user_payment* pay = new user_payment(this,UserName);
    pay->setFixedSize(pay->width(),pay->height());
    DB.Disconnect();
    pay->exec();
    DB.Connect();
    Search(ui->txt_search->text(),0);
}

void user_part::on_btn_history_clicked()
{
    delete model;
    Shop_history* his = new Shop_history(this);
    his->setFixedSize(his->width(),his->height());
    his->exec();
    Search(ui->txt_search->text(),0);
}

void user_part::on_btn_viewfavorite_clicked()
{
    delete model;
    favorites* fav = new favorites(this,UsrID);
    fav->setFixedSize(fav->width(),fav->height());
    fav->exec();
    Search(ui->txt_search->text(),0);
}


void user_part::load_data(QString username){

    // get data from DB and set them in form:

    QString query_str;
    QSqlQuery query;

    query_str = "select firstname,lastname,"
                "email,wallet,attachments,\"Customer ID\" "
                "from customers "
                "where username = "
                "\'" + username +"\' ;";

    if(DB.Execute(query_str,query)){

        query.first();

        ui->txt_username->setText(username);
        ui->txt_firstname->setText(query.value(0).toString());
        ui->txt_lastname->setText(query.value(1).toString());
        ui->txt_email->setText(query.value(2).toString());
        ui->txt_wallet->setText(query.value(3).toString());

        UsrID = query.value(5).toInt();

        QByteArray PIC = query.value(4).toByteArray();
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

void user_part::set_form(){

    ui->txt_email->setDisabled(true);
    ui->txt_wallet->setDisabled(true);
    ui->txt_username->setDisabled(true);
    ui->txt_lastname->setDisabled(true);
    ui->txt_firstname->setDisabled(true);
    ui->pic_profile->setDisabled(true);
    ui->pic_profile->setEnabled(true);
}

void user_part::on_btn_logoff_clicked()
{
    Widget* w = new Widget(0);
    w->setFixedSize(w->width(),w->height());
    w->setGeometry(500,200,w->width(),w->height());
    this->close();
    w->show();
}

void user_part::Search(QString key, int Type){

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

void user_part::load_search_data(int ID){

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

    UCOST = UnitCost.toInt();

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

QString user_part::find_company(int id){

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

void user_part::Setup(){

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


void user_part::on_radio_Name_clicked()
{
    Search(ui->txt_search->text(),0);
}

void user_part::on_redio_Category_clicked()
{
    Search(ui->txt_search->text(),1);
}

void user_part::on_txt_search_textChanged(const QString &arg1)
{
    if(ui->radio_Name->isChecked()){
        Search(arg1,0);
    }
    else{
        Search(arg1,1);
    }
}

void user_part::on_tbl_search_clicked(const QModelIndex &index)
{
    P_ID = ui->tbl_search->model()->index(index.row(),0).data().toInt();
    load_search_data(P_ID);
}

bool user_part::isFavorite(int UsrID, int productID){
    QString query_str;
    QSqlQuery query;

    query_str = "select * from favorites where \"Customer ID\" = "  + QString::number(UsrID) +
            " and \"Product ID\" = + " + QString::number(productID) +  ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return true;
    }

    if(query.size() == 0){
        return false;
    }
    return true;
}

void user_part::on_btn_addtocart_clicked()
{
    QItemSelectionModel *select = ui->tbl_search->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    int CartID = has_unpaid_cart(UsrID);

    QString query_str;
    QSqlQuery query;


    if(CartID == 0){

        // new cart
        query_str = "insert into cart(\"Customer ID\", "
                    "\"Total price\",\"Pay status\", "
                    "\"Pay date\")values(" + QString::number(UsrID) +",0,0,null);";

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

        CartID = has_unpaid_cart(UsrID);
    }

    query_str.clear();
    query.clear();

    // add to cart item

    int quantity = ui->spin_stock->value();
    int total = quantity * UCOST;

    if(has_product_in_cart(CartID,P_ID) == false){

        query_str = "insert into cart_item values(" +
                    QString::number(CartID) + "," +
                    QString::number(P_ID) + "," +
                    QString::number(quantity) + "," +
                    QString::number(UCOST) + "," +
                    QString::number(total)+");";

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

    }
    else{

        query_str = "update cart_item "
                    " set quantity = quantity + " + QString::number(quantity) +
                    ", total_price = total_price + " + QString::number(total) +
                    " where \"Cart ID\" = " + QString::number(CartID) +
                    " and \"Product ID\" = " + QString::number(P_ID) + ";";

        if(DB.Execute(query_str,query) == false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

    }

    query.clear();
    query_str.clear();

    // add to cart

    query_str = "update cart set"
                " \"Total price\" = \"Total price\" "
                " + " + QString::number(total) +
                " where \"Cart ID\" = " + QString::number(CartID) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    QMessageBox::about(this,"Successful","Added to your cart");
}

void user_part::on_btn_addtofavorite_clicked()
{
    QItemSelectionModel *select = ui->tbl_search->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    if(isFavorite(UsrID,P_ID)){
        QMessageBox::warning(this,"Input error","this stock exists in your Favorite List");
        return;
    }

    QString query_str;
    QSqlQuery query;

    query_str = "insert into favorites values("+ QString::number(UsrID) + "," + QString::number(P_ID) + ");";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    QMessageBox::about(this,"Successful","Added to your favorite list");
}

int user_part::has_unpaid_cart(int usrid){
    /// return open cart ID
    QString query_str;
    QSqlQuery query;


    query_str = "select * from cart where \"Customer ID\" = " + QString::number(usrid) + " and \"Pay status\" = 0;";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return false;
    }

    if(query.size() == 0){
        return 0;
    }
    else{
        query.first();
        return query.value(0).toInt();
    }
}

bool user_part::has_product_in_cart(int cart, int productid){

    QString query_str;
    QSqlQuery query;

    query_str = "select * from cart_item where "
                "\"Cart ID\" = " + QString::number(cart) +
                " and \"Product ID\" = " + QString::number(productid) + ";";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return false;
    }

    if(query.size() == 0){
        return false;
    }
    else {
        return true;
    }

}
