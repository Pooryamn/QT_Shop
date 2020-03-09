#ifndef VERIFY_EMPLOYEE_H
#define VERIFY_EMPLOYEE_H

#include <QDialog>

namespace Ui {
class verify_employee;
}

class verify_employee : public QDialog
{
    Q_OBJECT

public:
    explicit verify_employee(QWidget *parent = nullptr);
    void SetPass(QString emp,QString mas);
    ~verify_employee();

private:
    Ui::verify_employee *ui;
    QString Employee;
    QString Master;
};

#endif // VERIFY_EMPLOYEE_H
