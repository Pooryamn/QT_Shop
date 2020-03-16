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
    Database DB; // database object
    int Type; // type of form performance (0 : add supplier , 1 : view and edit supplier)
    int ID; // Supplier ID
    QByteArray image; // stores supplier logo

    bool check_input();  // chech that inputs be ok to save in database
    bool isValidSupplier(QString name);// gets the name of supplier and check supplier has exists or not
    void load_data(int id); // gets supplier id and load supplier info in form
};

#endif // NEW_SUPPLIER_H
