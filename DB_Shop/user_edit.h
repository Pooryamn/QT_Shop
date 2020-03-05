#ifndef USER_EDIT_H
#define USER_EDIT_H

#include <QDialog>

namespace Ui {
class user_edit;
}

class user_edit : public QDialog
{
    Q_OBJECT

public:
    explicit user_edit(QWidget *parent = nullptr);
    ~user_edit();

private:
    Ui::user_edit *ui;
    void setup();
};

#endif // USER_EDIT_H
