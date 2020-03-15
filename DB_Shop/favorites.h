#ifndef FAVORITES_H
#define FAVORITES_H

#include <QDialog>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class favorites;
}

class favorites : public QDialog
{
    Q_OBJECT

public:
    explicit favorites(QWidget *parent = nullptr,int UsrID=0);
    ~favorites();

private slots:
    void on_btn_delete_clicked();

    void on_tbl_history_clicked(const QModelIndex &index);

private:
    Ui::favorites *ui;
    Database DB;
    int USER_ID;
    int PRODUCT_ID;
    void load_data(int id);
    QSqlQueryModel* model;
};

#endif // FAVORITES_H
