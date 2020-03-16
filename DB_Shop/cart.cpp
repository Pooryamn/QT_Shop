#include "cart.h"
#include "ui_cart.h"

Cart::Cart(QWidget *parent,int usrid) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);

    DB.Connect();
    if(DB.IsConnected() == false){
        qDebug() << "Database Connection Error";
        exit(0);
    }

    ui->txt_total->setReadOnly(true);

    USER_ID = usrid;

    load_data(USER_ID);


}

Cart::~Cart()
{
    delete model;
    DB.Disconnect();
    delete ui;
}

void Cart::load_data(int user_id){

    int TOTAL_PRICE ;
    CartID = find_active_cart_Total(user_id,TOTAL_PRICE);

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Product name\",category, "
                "cart_item.\"Unit cost\",quantity, "
                "total_price,cart_item.\"Product ID\" from cart_item inner "
                "join products on cart_item.\"Product ID\" "
                "= products.\"Product ID\" where \"Cart ID\" = " + QString::number(CartID) + ";" ;

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    model = new QSqlQueryModel(this);

    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,"P_Name");
    model->setHeaderData(1,Qt::Horizontal,"Category");
    model->setHeaderData(2,Qt::Horizontal,"Cost");
    model->setHeaderData(3,Qt::Horizontal,"Quantity");
    model->setHeaderData(4,Qt::Horizontal,"Total");


    ui->tbl_cart->setModel(model);

    ui->tbl_cart->setColumnWidth(0,200);
    ui->tbl_cart->setColumnWidth(1,200);
    ui->tbl_cart->setColumnWidth(2,150);
    ui->tbl_cart->setColumnWidth(3,150);
    ui->tbl_cart->setColumnWidth(4,200);
    ui->tbl_cart->setColumnWidth(5,0);


    ui->tbl_cart->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->txt_total->setText(QString::number(TOTAL_PRICE));


}

int Cart::find_active_cart_Total(int user_id, int &Total){

    QString query_str;
    QSqlQuery query;

    query_str = "select * from cart where "
                "\"Customer ID\" = " + QString::number(user_id) + " and \"Pay status\" = 0";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return 0;
    }

    query.first();

    Total = query.value(2).toInt();
    return  query.value(0).toInt();

}

void Cart::on_btn_delete_clicked()
{
    QItemSelectionModel *select = ui->tbl_cart->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input error","First select a data");
        return;
    }

    QModelIndex idx =  select->currentIndex();
    int row = idx.row();

    int ProductID = ui->tbl_cart->model()->index(row,5).data().toInt();
    int cu_price = ui->tbl_cart->model()->index(row,4).data().toInt();

    QSqlQuery query;
    QString query_str;

    query_str = "delete from cart_item where "
                "\"Cart ID\" = " + QString::number(CartID) +
                " and \"Product ID\" = " + QString::number(ProductID) + ";";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    query.clear();
    query_str.clear();

    query_str = "update cart"
                " set \"Total price\" = \"Total price\" - " + QString::number(cu_price) +
                " where \"Cart ID\" = " + QString::number(CartID) + ";";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return;
    }

    load_data(USER_ID);
}

void Cart::on_btn_pay_clicked()
{
    int Price = ui->txt_total->text().toInt();
    int wallet = Get_wallet(USER_ID);

    if(Price > wallet){
        QMessageBox::warning(this,"Wallet Error","You dont have enough money to pay this cart");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Confrim","Are You sure to pay?");

    if (reply == QMessageBox::Yes) {
        //pay
        QString query_str;
        QSqlQuery query;

        QString Pay_Date = DateConverter();

        query_str = "update cart"
                    " set \"Pay status\" = 1,"
                    " \"Pay date\" = \'" + Pay_Date + "\'"
                    " where \"Cart ID\" = " + QString::number(CartID) + ";";

        if(DB.Execute(query_str,query) ==false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

        query.clear();
        query_str.clear();

        query_str = "update customers"
                    " set wallet = wallet - " + QString::number(Price) +
                    " where \"Customer ID\" = " + QString::number(USER_ID) + ";";


        if(DB.Execute(query_str,query) ==false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

        query.clear();
        query_str.clear();

        if(add_transaction(USER_ID,Price,Pay_Date) == false){
            return;
        }

        query.clear();
        query_str.clear();

        query_str = "select \"Product ID\", "
                    "quantity from cart_item"
                    " where \"Cart ID\" = " + QString::number(CartID) + ";";

        if(DB.Execute(query_str,query) ==false){
            qDebug() << query.lastQuery() << endl<<query.lastError();
            return;
        }

        query.first();

        for(int i = 0;i < query.size();i++){
            update_stock(query.value(0).toInt(),query.value(1).toInt());
            query.next();
        }

        load_data(USER_ID);

    }
    else {
        return;
      }

}


int Cart::Get_wallet(int usrid){
    QSqlQuery query;
    QString query_str;

    query_str = "select wallet from customers where \"Customer ID\" = " + QString::number(usrid) + ";";

    if(DB.Execute(query_str,query) ==false){
        qDebug() << query.lastQuery() << endl<<query.lastError();
        return 0;
    }

    query.first();

    return query.value(0).toInt();
}

QString Cart::DateConverter(){

    //get date:
    int year,month,day;
    QDate::currentDate().getDate(&year,&month,&day);
    QString pay_date = QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day);

    QDateConvertor convert;
    QStringList shamsi_list = convert.ToJalali(QString::number(year),QString::number(month),QString::number(day));

    QString result = shamsi_list[0] + "-" + shamsi_list[1] + "-" + shamsi_list[2];

    qDebug() << result;

    return result;
}

bool Cart::add_transaction(int id, int ammount, QString date){

    QString query_str;
    QSqlQuery query;

    query_str = "insert into transactions("
                "\"Customer ID\" , \"Transaction type\","
                "\"Transaction amount\",\"Transaction status\","
                "\"Transaction date\") values"
                "(" + QString::number(id) + ", \'Buy\',"
                +QString::number(ammount) + ", \'successful\' ,"
                "\'" + date + "\' );";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return false;
    }
    return true;

}

bool Cart::update_stock(int P_id,int quantity){
    QString query_str;
    QSqlQuery query;

    query_str = "update products set "
                "stock = stock - " + QString::number(quantity) +
                " where \"Product ID\" = " + QString::number(P_id);

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return false;
    }
    return true;

}
