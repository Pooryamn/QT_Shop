#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <QDialog>

namespace Ui {
class Suppliers;
}

class Suppliers : public QDialog
{
    Q_OBJECT

public:
    explicit Suppliers(QWidget *parent = nullptr);
    ~Suppliers();

private:
    Ui::Suppliers *ui;
};

#endif // SUPPLIERS_H
