#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>


class Database
{
public:

    Database();
    int Connect(); // try to connect and return status as int
    void Disconnect(); // Disconnet Object from database
    bool Execute(QString& qry,QSqlQuery& query); // get a valid query and try to execute it. if executing was successful return true otherwise return false
    bool IsConnected(); // check that object is connected to databae or not

private:

    QSqlDatabase DB;
    QString error; // store last error from database
    bool Connection_Status; // if connection is ok(true) otherwise (false)
    bool Create_DB(); // create database tables

};

#endif // DATABASE_H
