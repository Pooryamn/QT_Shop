#ifndef USER_PAYMENT_H
#define USER_PAYMENT_H

#include <QDialog>

#include "gateway.h"

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
};

#endif // USER_PAYMENT_H
