#ifndef USER_PART_H
#define USER_PART_H

#include <QDialog>

#include "cart.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "favorites.h"
#include "database.h"
#include "widget.h"

namespace Ui {
class user_part;
}

class user_part : public QDialog
{
    Q_OBJECT

public:
    explicit user_part(QWidget *parent = nullptr,QString usr="");

    ~user_part();

public slots:

    void on_btn_resizer_clicked();

private slots:
    void on_btn_Cart_clicked();

    void on_btn_ediprofile_clicked();

    void on_btn_payment_clicked();

    void on_btn_history_clicked();

    void on_btn_viewfavorite_clicked();


    void on_btn_logoff_clicked();

    void on_radio_Name_clicked();

    void on_redio_Category_clicked();

    void on_txt_search_textChanged(const QString &arg1);

    void on_tbl_search_clicked(const QModelIndex &index);

    void on_btn_addtocart_clicked();

    void on_btn_addtofavorite_clicked();

private:

    Ui::user_part *ui;
    QString UserName;
    Database DB; // database object
    QByteArray image[6]; // array of bytearrays for product image
    QSqlQueryModel* model; // sql query result model
    int UsrID;
    int P_ID; // product id
    int UCOST; // unit cost of selected product

    void load_data(QString username); // load user info in ui
    void set_form(); // set some rules for ui
    void Search(QString key,int Type); // search engine
    void load_search_data(int ID); // load product info in ui by using produt id
    QString find_company(int id);//gets company id and returns company name
    void Setup(); // initialize form
    bool isFavorite(int UsrID,int productID); //check that the product exists in user favorite list or not
    int has_unpaid_cart(int usrid); // check that user has unpaid cart or not( to decide create a new cart or not)
    bool has_product_in_cart(int cart,int productid);// check that a specia product exists in cart items or not(to decide to add stock or all info to the table)
    int get_stock(int P_id);// gets product id and return its stock
};

#endif // USER_PART_H
