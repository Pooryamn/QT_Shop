#ifndef USER_PART_H
#define USER_PART_H

#include <QDialog>

#include "cart.h"

namespace Ui {
class user_part;
}

class user_part : public QDialog
{
    Q_OBJECT

public:
    explicit user_part(QWidget *parent = nullptr);
    ~user_part();

public slots:

    void on_btn_resizer_clicked();

private slots:
    void on_btn_Cart_clicked();

private:
    Ui::user_part *ui;
};

#endif // USER_PART_H
