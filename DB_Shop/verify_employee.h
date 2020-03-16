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
    void SetPass(QString emp,QString mas); // employee code and master code
    bool get_status(); // true -> if codes confrim successfully
    ~verify_employee();

private slots:
    void on_btn_edit_clicked();

    void on_btn_verify_clicked();

private:
    Ui::verify_employee *ui;
    QString Employee;//employee confrom code
    QString Master; // master confrom code
    bool status; // true -> if codes confrim successfully
};

#endif // VERIFY_EMPLOYEE_H
