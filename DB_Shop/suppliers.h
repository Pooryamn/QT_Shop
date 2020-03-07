#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <QDialog>

#include "new_supplier.h"

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

private:
    Ui::Suppliers *ui;
};

#endif // SUPPLIERS_H
