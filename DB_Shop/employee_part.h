#ifndef EMPLOYEE_PART_H
#define EMPLOYEE_PART_H

#include <QDialog>

namespace Ui {
class employee_part;
}

class employee_part : public QDialog
{
    Q_OBJECT

public:
    explicit employee_part(QWidget *parent = nullptr);
    ~employee_part();

public slots:
    void on_btn_resizer_clicked();

private:
    Ui::employee_part *ui;
};

#endif // EMPLOYEE_PART_H
