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
    ~Suppliers();

private slots:
    void on_btn_addsupplier_clicked();

    void on_btn_deletesupplier_clicked();

private:
    Ui::Suppliers *ui;
    Database DB;
    void Load_data();
};

#endif // SUPPLIERS_H
