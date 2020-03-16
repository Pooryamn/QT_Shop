#ifndef USER_PAYMENT_H
#define USER_PAYMENT_H

#include <QDialog>

#include "gateway.h"
#include "database.h"
#include "Date/qdateconvertor.h"

namespace Ui {
class user_payment;
}

class user_payment : public QDialog
{
    Q_OBJECT

public:
    explicit user_payment(QWidget *parent = nullptr,QString usrname="");
    ~user_payment();

private slots:
    void on_btn_addpayment_clicked();

private:
    Ui::user_payment *ui;
    QString UserName;
    Database DB; // database object

    int find_id(QString username); // gets username and return user id
    bool add_transaction(int id,int ammount,QString date);//add data to transaction table
    bool add_wallet(int ID,int ammount);// update wallet ammount for user
    void load_data(QString username); // load user data to ui
    QString DateConverter(); // convert current date to shamsi date
    int get_type(QString username); // gets username and return type of user
    void load_all();// load all payments of all users(for employee and master level)
};

#endif // USER_PAYMENT_H
