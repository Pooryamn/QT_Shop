#ifndef EMPLOYEE_PART_H
#define EMPLOYEE_PART_H

#include <QDialog>

#include "new_stock.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "database.h"

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

private:

    Ui::employee_part *ui;
    QString UserName;
    Database DB;
    void set_form();
    void load_data(QString username);
};

#endif // EMPLOYEE_PART_H
