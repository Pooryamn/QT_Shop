#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <QDialog>

#include "new_supplier.h"
#include "database.h"

namespace Ui {
class Suppliers;
}

class Suppliers : public QDialog
{
    Q_OBJECT

public:
    explicit Suppliers(QWidget *parent = nullptr);
    int edit_supplier_called();
    ~Suppliers();

private slots:
    void on_btn_addsupplier_clicked();

    void on_btn_deletesupplier_clicked();

    void on_tbl_suppliers_doubleClicked(const QModelIndex &index);

private:
    Ui::Suppliers *ui;
    Database DB;
    void Load_data();
    int supplier_called;
};

#endif // SUPPLIERS_H
