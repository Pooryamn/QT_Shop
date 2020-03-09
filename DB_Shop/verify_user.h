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
    void SetPass(QString Usr);
    bool get_status();
    ~Verify_User();

private slots:
    void on_btn_edit_clicked();

    void on_btn_verify_clicked();

private:
    Ui::Verify_User *ui;
    QString User;
    bool Status;
};

#endif // VERIFY_USER_H
