#ifndef FAVORITES_H
#define FAVORITES_H

#include <QDialog>

namespace Ui {
class favorites;
}

class favorites : public QDialog
{
    Q_OBJECT

public:
    explicit favorites(QWidget *parent = nullptr);
    ~favorites();

private:
    Ui::favorites *ui;
};

#endif // FAVORITES_H
