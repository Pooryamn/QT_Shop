#ifndef USER_PART_H
#define USER_PART_H

#include <QDialog>

#include "cart.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "favorites.h"
#include "database.h"
#include "widget.h"

namespace Ui {
class user_part;
}

class user_part : public QDialog
{
    Q_OBJECT

public:
    explicit user_part(QWidget *parent = nullptr,QString usr="");

    ~user_part();

public slots:

    void on_btn_resizer_clicked();

private slots:
    void on_btn_Cart_clicked();

    void on_btn_ediprofile_clicked();

    void on_btn_payment_clicked();

    void on_btn_history_clicked();

    void on_btn_viewfavorite_clicked();


    void on_btn_logoff_clicked();

    void on_radio_Name_clicked();

    void on_redio_Category_clicked();

    void on_txt_search_textChanged(const QString &arg1);

    void on_tbl_search_clicked(const QModelIndex &index);

    void on_btn_addtocart_clicked();

private:
    Ui::user_part *ui;
    QString UserName;

    Database DB;

    void load_data(QString username);
    void set_form();

    void Search(QString key,int Type);
    void load_search_data(int ID);
    QString find_company(int id);
    QByteArray image[6];
    void Setup();

    QSqlQueryModel* model;

    bool isFavorite(int UsrID,int productID);

    int UsrID;
    int P_ID;
};

#endif // USER_PART_H
