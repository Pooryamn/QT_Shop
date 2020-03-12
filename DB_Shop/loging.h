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
    int get_type();
    QString get_user();
    ~Loging();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

    void on_btn_forget_clicked();

    void on_txt_User_editingFinished();

private:
    Ui::Loging *ui;

    Database DB;

    void connect_to_db();
    bool check_inputs();
    bool check_information();

    int User_type;

};

#endif // LOGING_H
