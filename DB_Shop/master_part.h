#ifndef MASTER_PART_H
#define MASTER_PART_H

#include <QDialog>

#include "new_stock.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "users.h"
#include "master_signup.h"
#include "suppliers.h"
#include "new_supplier.h"
#include "database.h"
#include "widget.h"

namespace Ui {
class master_part;
}

class master_part : public QDialog
{
    Q_OBJECT

public:
    explicit master_part(QWidget *parent = nullptr,QString usrname="");
    ~master_part();

public slots:
    void on_btn_resizer_clicked();

private slots:
    void on_btn_newstock_clicked();

    void on_btn_ediprofile_clicked();

    void on_btn_payment_clicked();

    void on_btn_history_clicked();

    void on_btn_viewuser_clicked();

    void on_btn_addmaster_clicked();

    void on_btn_supplier_clicked();

    void on_btn_logoff_clicked();

    void on_radio_Name_clicked();

    void on_redio_Category_clicked();

    void on_txt_search_textChanged(const QString &arg1);


    void on_tbl_search_clicked(const QModelIndex &index);

    void on_btn_addstock_clicked();

private:
    Ui::master_part *ui;
    QString UserName;
    Database DB;
    void set_form();
    void load_data(QString username);
    void Search(QString key,int Type);
    void load_search_data(int ID);
    QString find_company(int id);
    QByteArray image[6];
    void Setup();

    QSqlQueryModel* model;
};

#endif // MASTER_PART_H
