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
    Database DB;
    QString Username;
    int User_type;
    void setup();
    void load_data(QString& username,int type);
    bool check_inputs();
    bool Pass_Changed;
    QByteArray image;
};

#endif // USER_EDIT_H
