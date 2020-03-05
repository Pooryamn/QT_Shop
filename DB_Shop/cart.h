#ifndef CART_H
#define CART_H

#include <QDialog>

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    ~Cart();

private:
    Ui::Cart *ui;
};

#endif // CART_H
