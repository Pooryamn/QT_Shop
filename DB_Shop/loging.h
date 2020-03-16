#ifndef LOGING_H
#define LOGING_H

#include <QDialog>
#include <QDebug>

#include "forget.h"
#include <database.h>
#include <QMessageBox>

namespace Ui {
class Loging;
}

class Loging : public QDialog
{
    Q_OBJECT

public:
    explicit Loging(QWidget *parent = nullptr);
    int get_type(); // returns User_type(for security perposes)
    QString get_user(); // returns entered username(for security perposes)
    ~Loging();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

    void on_btn_forget_clicked();

    void on_txt_User_editingFinished();

private:
    Ui::Loging *ui;
    Database DB; // database object
    int User_type;

    bool check_inputs(); // after login button clicked this function checks inputs
    bool check_information(); // check that username and password is in Database


};

#endif // LOGING_H
