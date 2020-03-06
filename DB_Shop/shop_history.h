#ifndef SHOP_HISTORY_H
#define SHOP_HISTORY_H

#include <QDialog>

namespace Ui {
class Shop_history;
}

class Shop_history : public QDialog
{
    Q_OBJECT

public:
    explicit Shop_history(QWidget *parent = nullptr);
    ~Shop_history();

private:
    Ui::Shop_history *ui;
};

#endif // SHOP_HISTORY_H
