#ifndef VERIFY_EMPLOYEE_H
#define VERIFY_EMPLOYEE_H

#include <QDialog>
#include "QMessageBox"

namespace Ui {
class verify_employee;
}

class verify_employee : public QDialog
{
    Q_OBJECT

public:
    explicit verify_employee(QWidget *parent = nullptr);
    void SetPass(QString emp,QString mas);
    bool get_status();
    ~verify_employee();

private slots:
    void on_btn_edit_clicked();

    void on_btn_verify_clicked();

private:
    Ui::verify_employee *ui;
    QString Employee;
    QString Master;
    bool status;
};

#endif // VERIFY_EMPLOYEE_H
