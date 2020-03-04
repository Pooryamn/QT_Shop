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

private:
    Ui::Widget *ui;
    void Setup();
    void Check_Connection();

};

#endif // WIDGET_H
