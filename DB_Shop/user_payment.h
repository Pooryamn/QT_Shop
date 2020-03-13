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
    Database DB;
    int find_id(QString username);
    bool add_transaction(int id,int ammount,QString date);
    bool add_wallet(int ID,int ammount);
    void load_data(QString username);
    QString DateConverter();
};

#endif // USER_PAYMENT_H
