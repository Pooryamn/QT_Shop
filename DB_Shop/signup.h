#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QFileDialog>

#include "widget.h"
#include "verify_user.h"
#include "verify_employee.h"
#include "database.h"
#include "mail/SmtpMime"


namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_SignUp_finished(int result);

    void on_btn_close_clicked();

    void on_btn_cansel_clicked();

    void on_radio_user_clicked();

    void on_redio_employee_clicked();

    void on_btn_verify_clicked();

    void on_btn_load_clicked();

    void on_btn_clear_clicked();

    void on_txt_year_editingFinished();

    void on_txt_user_editingFinished();

private:
    Ui::SignUp *ui;
    Database DB; // database object
    bool profile_filled; // true -> user wants to save profile pic in database
    QByteArray image; // store image to save it in database

    void set_input_methods(); // set some rules for inputs
    bool check_inputs(); // check that inputs be ok for saving in database
    bool add_to_accounts(int type); // store username , password , type in account table
    bool is_valid_User();// check that user exists in database or not
    bool Send_Email(QString Email,QString Name,QString Subject,QString Body);//send confrim code to user email
    QString RandStr(); // generate a random string with lenght =6

};

#endif // SIGNUP_H
