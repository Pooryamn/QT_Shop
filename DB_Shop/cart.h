#ifndef CART_H
#define CART_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include <Date/qdateconvertor.h>


namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr,int usrid=0);
    ~Cart();

private slots:
    void on_btn_delete_clicked();

    void on_btn_pay_clicked();

private:
    //Vars :
    Ui::Cart *ui;
    Database DB; // Database Object
    int USER_ID;
    int CartID;
    QSqlQueryModel* model; // Model for QTable view (connect Query to table)

    // funcs :
    void load_data(int user_id); // Load Cart data for User
    int find_active_cart_Total(int user_id,int& Total); // find a cart ID for user that status is Unpain(0)
    int Get_wallet(int usrid); // find wallet ammount for UserID
    QString DateConverter(); // Convert current date to shamsi date
    bool add_transaction(int id, int ammount, QString date); // add a new transaction row in table with arguments
    bool update_stock(int P_id,int quantity); // substract quantity from stock in Product with P_ID

};

#endif // CART_H
