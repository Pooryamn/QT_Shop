#ifndef FORGET_H
#define FORGET_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "mail/SmtpMime"

namespace Ui {
class forget;
}

class forget : public QDialog
{
    Q_OBJECT

public:
    explicit forget(QWidget *parent = nullptr);
    ~forget();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_recover_clicked();

private:
    Ui::forget *ui;
    Database DB;
    QString find_email(QString username,int type);
    QString find_password(QString username,int& type);
    bool Send_Email(QString Email,QString Name,QString Subject,QString Body);
    bool is_valid_User();
    int Type;
};

#endif // FORGET_H
