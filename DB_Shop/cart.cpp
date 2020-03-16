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
