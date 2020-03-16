#ifndef CART_H
#define CART_H

#include <QDialog>
#include <database.h>
#include <Date/qdateconvertor.h>
#include <QMessageBox>

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr,int usrid=0);
    ~Cart();

private slots:
    void on_btn_delete_clicked();

    void on_btn_pay_clicked();

private:
    Ui::Cart *ui;
    Database DB;

    int USER_ID;
    int CartID;

    void load_data(int user_id);
    int find_active_cart_Total(int user_id,int& Total);
    QSqlQueryModel* model;
    int Get_wallet(int usrid);
    QString DateConverter();
    bool add_transaction(int id, int ammount, QString date);
};

#endif // CART_H
