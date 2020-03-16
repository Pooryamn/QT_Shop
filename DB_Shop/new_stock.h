#ifndef NEW_STOCK_H
#define NEW_STOCK_H

#include <QDialog>
#include <QFileDialog>

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
    bool new_supplier_called(); // return true if new supplier button pressed in ui(Security)
    ~new_stock();

private slots:
    void on_btn_addsupplier_clicked();

    void on_tbl_supplier_clicked(const QModelIndex &index);

    void on_btn_choose1_clicked();

    void on_btn_choose2_clicked();

    void on_btn_choose3_clicked();

    void on_btn_choose4_clicked();

    void on_btn_choose5_clicked();

    void on_btn_choose6_clicked();

    void on_btn_addstock_clicked();

private:

    Ui::new_stock *ui;
    Database DB; // database object
    QByteArray image[6]; // array of bytearrays for storing pics
    int SupplierID;
    int ProductID;
    QSqlQueryModel* model;//sql query result model

    void load_suppliers(); // load all suppliers name and id in table view
    bool supplier_called; // true -> if new supplier button pressed
    void set_input_method(); // set some rules for inputs
    bool check_inputs(); // check inputs to be ok for storing in database
    QString get_category(QString Company); // gets company name and return its category
    bool isValidProduct(int SuppID,QString PName); // gets product name and company name and check that product exists in database or not

};

#endif // NEW_STOCK_H
