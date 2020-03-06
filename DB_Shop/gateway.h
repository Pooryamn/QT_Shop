#ifndef GATEWAY_H
#define GATEWAY_H

#include <QDialog>

namespace Ui {
class gateway;
}

class gateway : public QDialog
{
    Q_OBJECT

public:
    explicit gateway(QWidget *parent = nullptr);
    ~gateway();

private:
    Ui::gateway *ui;
};

#endif // GATEWAY_H
