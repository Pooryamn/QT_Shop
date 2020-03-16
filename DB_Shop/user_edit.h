#ifndef USER_EDIT_H
#define USER_EDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>

#include "database.h"

namespace Ui {
class user_edit;
}

class user_edit : public QDialog
{
    Q_OBJECT

public:
    explicit user_edit(QWidget *parent = nullptr,QString usrname="",int type=0);
    ~user_edit();

private slots:
    void on_btn_save_clicked();

    void on_btn_clear_clicked();

    void on_btn_load_clicked();

    void on_btn_cansel_clicked();

    void on_btn_close_clicked();

private:
    Ui::user_edit *ui;
    Database DB; // database object
    QString Username;
    int User_type;
    bool Pass_Changed; // true -> if user want to change password
    QByteArray image; // store user profile to save in database

    void setup(); // initialize form
    void load_data(QString& username,int type); // gets the username and type of user and load all info
    bool check_inputs();// check that inputs are ok or not

};

#endif // USER_EDIT_H
