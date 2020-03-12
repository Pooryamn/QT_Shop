#ifndef USER_PART_H
#define USER_PART_H

#include <QDialog>

#include "cart.h"
#include "user_edit.h"
#include "user_payment.h"
#include "shop_history.h"
#include "favorites.h"
#include "database.h"

namespace Ui {
class user_part;
}

class user_part : public QDialog
{
    Q_OBJECT

public:
    explicit user_part(QWidget *parent = nullptr,QString usr="");
    void set_user(QString username);

    ~user_part();

public slots:

    void on_btn_resizer_clicked();

private slots:
    void on_btn_Cart_clicked();

    void on_btn_ediprofile_clicked();

    void on_btn_payment_clicked();

    void on_btn_history_clicked();

    void on_btn_viewfavorite_clicked();


private:
    Ui::user_part *ui;
    QString UserName;

    Database DB;

    void load_data(QString username);
    void set_form();
};

#endif // USER_PART_H
