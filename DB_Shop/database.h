#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>


class Database
{
public:
    Database();
    int Connect();
private:

    QSqlDatabase DB;

    QString error;
    bool Connection_Status;
    bool Connection_Status2;

    bool New_DB();


};

#endif // DATABASE_H
