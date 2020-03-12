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

#endif // MASTER_SIGNUP_H
