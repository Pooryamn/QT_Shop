#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>


class Database
{
public:
    Database();
    int Connect();
    void Disconnect();
    bool Execute(QString query);
private:

    QSqlDatabase DB;

    QString error;

    bool Connection_Status;

    bool Create_DB();

    bool New_DB();
};

#endif // DATABASE_H
