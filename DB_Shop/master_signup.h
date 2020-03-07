#ifndef MASTER_SIGNUP_H
#define MASTER_SIGNUP_H

#include <QDialog>

#include "verify_employee.h"

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

private:
    Ui::Master_signup *ui;
};

#endif // MASTER_SIGNUP_H
