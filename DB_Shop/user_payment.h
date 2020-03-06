#ifndef USER_PAYMENT_H
#define USER_PAYMENT_H

#include <QDialog>

namespace Ui {
class user_payment;
}

class user_payment : public QDialog
{
    Q_OBJECT

public:
    explicit user_payment(QWidget *parent = nullptr);
    ~user_payment();

private:
    Ui::user_payment *ui;
};

#endif // USER_PAYMENT_H
