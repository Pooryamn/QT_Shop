#ifndef WIDGET_H
#define WIDGET_H


// QT Headers :
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>

// My headers:
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

    void on_tbl_search_clicked(const QModelIndex &index);

    void on_pic_1_clicked();

    void on_pic_2_clicked();

    void on_pic_3_clicked();

    void on_pic_4_clicked();

    void on_pic_5_clicked();

    void on_pic_6_clicked();

private:
    Ui::Widget *ui;
    Database DB; //database object
    QByteArray image[6]; // array of bytearrays for storing image
    QSqlQueryModel* model; // sql query result model

    void Setup(); // initialize ui form
    void Check_Connection();
    void Connect_DB();
    void Search(QString key,int Type); // serch engine
    void load_search_data(int ID); // gets product id and load info to ui
    QString find_company(int id);//gets company id and return compant name

};

#endif // WIDGET_H
