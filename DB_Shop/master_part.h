#ifndef MASTER_PART_H
#define MASTER_PART_H

#include <QDialog>

namespace Ui {
class master_part;
}

class master_part : public QDialog
{
    Q_OBJECT

public:
    explicit master_part(QWidget *parent = nullptr);
    ~master_part();

private:
    Ui::master_part *ui;
};

#endif // MASTER_PART_H
