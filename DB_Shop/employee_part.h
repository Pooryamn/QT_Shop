#ifndef EMPLOYEE_PART_H
#define EMPLOYEE_PART_H

// QT headers :
#include <QDialog>

// My headers :
#include "new_stock.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "database.h"
#include "widget.h"
#include "new_supplier.h"

namespace Ui {
class employee_part;
}

class employee_part : public QDialog
{
    Q_OBJECT

public:
    explicit employee_part(QWidget *parent = nullptr,QString usrname="");

    ~employee_part();

public slots:
    void on_btn_resizer_clicked();

private slots:
    void on_btn_newstock_clicked();

    void on_btn_ediprofile_clicked();

    void on_btn_payment_clicked();

    void on_btn_history_clicked();

    void on_btn_logoff_clicked();

    void on_txt_search_textChanged(const QString &arg1);

    void on_tbl_search_clicked(const QModelIndex &index);

    void on_btn_addstock_clicked();

    void on_radio_Name_clicked();

    void on_redio_Category_clicked();

private:

    //vars :
    Ui::employee_part *ui;
    QString UserName; // Employee username for using in functions
    Database DB; // Database Object
    QByteArray image[6]; //Array of Bytearrays for storing
    QSqlQueryModel* model; // Model of Sql Query results

    // funcs :
    void load_data(QString username); // load Employee information in ui form

    // Search Products with a search key and type(0 = search by name , 1 = search by category)
    void Search(QString key,int Type);
    void load_search_data(int ID);// load product info + pics in ui form
    QString find_company(int id); // gets Company ID and return name of company
    void Setup(); // set basics settings for ui form(disabling object , clear pics)
    void set_form(); // set some rule for objets in ui


};

#endif // EMPLOYEE_PART_H
