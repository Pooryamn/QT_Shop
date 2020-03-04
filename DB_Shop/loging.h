#ifndef LOGING_H
#define LOGING_H

#include <QDialog>

namespace Ui {
class Loging;
}

class Loging : public QDialog
{
    Q_OBJECT

public:
    explicit Loging(QWidget *parent = nullptr);
    ~Loging();

private slots:
    void on_btn_cancel_clicked();

private:
    Ui::Loging *ui;
};

#endif // LOGING_H
