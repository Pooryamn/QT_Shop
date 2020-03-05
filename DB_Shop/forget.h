#ifndef FORGET_H
#define FORGET_H

#include <QDialog>

namespace Ui {
class forget;
}

class forget : public QDialog
{
    Q_OBJECT

public:
    explicit forget(QWidget *parent = nullptr);
    ~forget();

private:
    Ui::forget *ui;
};

#endif // FORGET_H
