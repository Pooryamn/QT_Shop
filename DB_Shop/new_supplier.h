#ifndef NEW_SUPPLIER_H
#define NEW_SUPPLIER_H

#include <QDialog>

namespace Ui {
class New_supplier;
}

class New_supplier : public QDialog
{
    Q_OBJECT

public:
    explicit New_supplier(QWidget *parent = nullptr);
    ~New_supplier();

private:
    Ui::New_supplier *ui;
};

#endif // NEW_SUPPLIER_H
