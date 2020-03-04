#ifndef VERIFY_USER_H
#define VERIFY_USER_H

#include <QDialog>

namespace Ui {
class Verify_User;
}

class Verify_User : public QDialog
{
    Q_OBJECT

public:
    explicit Verify_User(QWidget *parent = nullptr);
    ~Verify_User();

private:
    Ui::Verify_User *ui;
};

#endif // VERIFY_USER_H
