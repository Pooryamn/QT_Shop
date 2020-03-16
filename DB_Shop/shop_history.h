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

    Database DB;

    int USER_ID;

    void load_data(int usrid);
    QString DateConverter();
    int get_type(QString username);
    void load_all();
};

#endif // SHOP_HISTORY_H
