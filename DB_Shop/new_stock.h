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

    void on_tbl_supplier_clicked(const QModelIndex &index);

private:
    Ui::new_stock *ui;
    Database DB;
    void load_suppliers();
    bool supplier_called;
    void set_input_method();
    bool check_inputs();
    QString get_category(QString Company);

};

#endif // NEW_STOCK_H
