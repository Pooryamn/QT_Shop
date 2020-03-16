#ifndef SHOP_HISTORY_H
#define SHOP_HISTORY_H

#include <QDialog>

#include "database.h"

namespace Ui {
class Shop_history;
}

class Shop_history : public QDialog
{
    Q_OBJECT

public:
    explicit Shop_history(QWidget *parent = nullptr,int usrid = 0);
    ~Shop_history();

private:

    Ui::Shop_history *ui;
    Database DB; // database object
    int USER_ID;

    void load_data(int usrid); // gets user id and load cart of user that paid
    QString DateConverter();// gets current date and convert it to shamsi date
    void load_all();// load all users carts (for employee and master level)
};

#endif // SHOP_HISTORY_H
