#ifndef MASTER_SIGNUP_H
#define MASTER_SIGNUP_H

#include <QDialog>
#include <QFileDialog>


#include "verify_employee.h"
#include "verify_user.h"
#include "verify_employee.h"
#include "database.h"
#include "mail/SmtpMime"
#include "widget.h"

namespace Ui {
class Master_signup;
}

class Master_signup : public QDialog
{
    Q_OBJECT

public:
    explicit Master_signup(QWidget *parent = nullptr);
    ~Master_signup();

private slots:
    void on_btn_verify_clicked();

    void on_btn_close_clicked();

    void on_btn_cansel_clicked();

    void on_btn_load_clicked();

    void on_btn_clear_clicked();

private:
    Ui::Master_signup *ui;
    Database DB; //database object
    QByteArray image; // store profile image as bytearray to store in database
    bool profile_filled; // true = user wants to save his/her picture in database

    void set_input_methods(); // set some rules for input formats
    bool check_inputs(); // check that inputs are ok for storing or not
    bool add_to_accounts(int type); // set username and passwod and type in database account table
    bool is_valid_User(); // user exists in database or not
    bool Send_Email(QString Email,QString Name,QString Subject,QString Body); // sending confrim codes to users
    QString RandStr(); // generate a random string with a lengh = 6
};

#endif // MASTER_SIGNUP_H
