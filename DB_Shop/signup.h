#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "widget.h"
#include "verify_user.h"

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

    void on_btn_clear_2_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
