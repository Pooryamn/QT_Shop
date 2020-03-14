#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>

#include "help.h"
#include "signup.h"
#include "loging.h"
#include "user_part.h"
#include "employee_part.h"
#include "master_part.h"
#include "database.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_btn_help_clicked();

    void on_btn_register_clicked();

    void on_btn_login_clicked();

    void on_txt_search_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    Database DB;
    void Setup();
    void Check_Connection();
    void Connect_DB();
    void Search(QString key,int Type);

};

#endif // WIDGET_H
