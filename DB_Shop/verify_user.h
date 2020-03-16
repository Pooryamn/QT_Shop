#ifndef VERIFY_USER_H
#define VERIFY_USER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Verify_User;
}

class Verify_User : public QDialog
{
    Q_OBJECT

public:
    explicit Verify_User(QWidget *parent = nullptr);
    void SetPass(QString Usr); // user confrim code
    bool get_status(); // true -> if user confrim code successfully
    ~Verify_User();

private slots:
    void on_btn_edit_clicked();

    void on_btn_verify_clicked();

private:
    Ui::Verify_User *ui;
    QString User; // user confrim code
    bool Status;// true -> if user confrim code successfully
};

#endif // VERIFY_USER_H
