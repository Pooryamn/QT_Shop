#ifndef NEW_STOCK_H
#define NEW_STOCK_H

#include <QDialog>

#include "new_supplier.h"

namespace Ui {
class new_stock;
}

class new_stock : public QDialog
{
    Q_OBJECT

public:
    explicit new_stock(QWidget *parent = nullptr);
    ~new_stock();

private slots:
    void on_btn_addsupplier_clicked();

private:
    Ui::new_stock *ui;
};

#endif // NEW_STOCK_H
