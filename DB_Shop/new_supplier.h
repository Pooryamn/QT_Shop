#ifndef NEW_SUPPLIER_H
#define NEW_SUPPLIER_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>

#include "database.h"

namespace Ui {
class New_supplier;
}

class New_supplier : public QDialog
{
    Q_OBJECT

public:
    explicit New_supplier(QWidget *parent = nullptr,int T=0,int id=0);
    ~New_supplier();

private slots:
    void on_btn_clear_clicked();

    void on_btn_choose_clicked();

    void on_btn_save_clicked();

private:
    Ui::New_supplier *ui;
    Database DB;
    void check_input();
    int Type;
    int ID;
    QByteArray image;
    bool isValidSupplier(QString name);
};

#endif // NEW_SUPPLIER_H
