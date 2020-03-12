#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql>
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
    Database DB;

    void set_input_methods();
    bool check_inputs();
    bool profile_filled;
    bool add_to_accounts(int type);
    QByteArray image;
    bool is_valid_User();

    bool Send_Email(QString Email,QString Name,QString Subject,QString Body);

    QString RandStr();

};

#endif // SIGNUP_H
