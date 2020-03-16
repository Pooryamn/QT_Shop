#ifndef FORGET_H
#define FORGET_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "mail/SmtpMime"

namespace Ui {
class forget;
}

class forget : public QDialog
{
    Q_OBJECT

public:
    explicit forget(QWidget *parent = nullptr);
    ~forget();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_recover_clicked();

private:

    Ui::forget *ui;
    Database DB; // database object
    int Type; // Type of user( 1 = Normal User, 2 = Employee , 3 = master)

    QString find_email(QString username,int type); // gets the type and username and return email by searchin in Database
    QString find_password(QString username,int& type); // gets username and type and return password
    bool Send_Email(QString Email,QString Name,QString Subject,QString Body);// send an simple text email to user (contains password of user)
    bool is_valid_User(); // check that Username in ui is valid or not(is it in database or not?)

};

#endif // FORGET_H
