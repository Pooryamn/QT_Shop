#ifndef NEW_STOCK_H
#define NEW_STOCK_H

#include <QDialog>

#include "new_supplier.h"
#include "database.h"

namespace Ui {
class new_stock;
}

class new_stock : public QDialog
{
    Q_OBJECT

public:
    explicit new_stock(QWidget *parent = nullptr);
    bool new_supplier_called();
    ~new_stock();

private slots:
    void on_btn_addsupplier_clicked();

private:
    Ui::new_stock *ui;
    Database DB;
    void load_suppliers();
    bool supplier_called;

};

#endif // NEW_STOCK_H
