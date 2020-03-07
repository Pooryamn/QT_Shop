#ifndef MASTER_SIGNUP_H
#define MASTER_SIGNUP_H

#include <QDialog>

namespace Ui {
class Master_signup;
}

class Master_signup : public QDialog
{
    Q_OBJECT

public:
    explicit Master_signup(QWidget *parent = nullptr);
    ~Master_signup();

private:
    Ui::Master_signup *ui;
};

#endif // MASTER_SIGNUP_H
