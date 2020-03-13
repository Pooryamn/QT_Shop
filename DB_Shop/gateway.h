#ifndef GATEWAY_H
#define GATEWAY_H

#include <QDialog>
#include <QRegExpValidator>
#include <QMessageBox>

namespace Ui {
class gateway;
}

class gateway : public QDialog
{
    Q_OBJECT

public:
    explicit gateway(QWidget *parent = nullptr);
    int get_ammount();
    ~gateway();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_pay_clicked();

private:
    Ui::gateway *ui;
    void set_input_method();
    int Ammount;
};

#endif // GATEWAY_H
