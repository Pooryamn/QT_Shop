#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    ~Users();

private slots:
    void on_combo_type_currentIndexChanged(const QString &arg1);

    void on_btn_deleteuser_clicked();

private:
    Ui::Users *ui;
    Database DB;
    void load_data(QString type);
};

#endif // USERS_H
