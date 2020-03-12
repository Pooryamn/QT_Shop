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

private:
    Ui::master_part *ui;
    QString UserName;
    Database DB;
    void set_form();
    void load_data(QString username);
};

#endif // MASTER_PART_H
