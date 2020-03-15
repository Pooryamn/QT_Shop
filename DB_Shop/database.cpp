#include "database.h"


Database::Database()
{
}

int Database::Connect(){

    /// this function Connect Software to P_Shop Postgresql database
    /// if have some problem try to handle it.


    /*
        Results :
            0 : no error
            1 : Driver error
            2 : Databae does not exists
     */


    DB = QSqlDatabase::addDatabase("QPSQL"); // it is Postgresql Driver

    DB.setPort(5432);

    DB.setHostName("localhost");

    DB.setUserName("postgres");

    DB.setPassword("223843877"); // Defualt password = postgres

    DB.setDatabaseName("P_Shop");

    Connection_Status = DB.open();

    if (Connection_Status == true){
        return 0;
    }
    else {

        /*

         ALGORITHM :

            First find the problem
            If Problem is Driver so tell the user to install it
            If Problem is Not existing Database so create it
        */

        // find problem :
         error = DB.lastError().text();

        // if it has Driver problem :
        if(error.contains("Driver")){
            // Driver problem
            return 1;
        }
        else if(error.contains("exist")){
            // database does not exist
            // try to create it
            DB.close();

            DB.setDatabaseName("postgres");

            Connection_Status = DB.open();

            if(Connection_Status == true){

                // Create P_Shop Database ::
                QSqlQuery query;

                query.exec("CREATE DATABASE P_Shop ;");
                query.clear();

                DB.close();

                DB.setDatabaseName("P_Shop");

                Connection_Status = DB.open();

                if(Create_DB()){
                    return 0;
                }
                else{
                    return 2;
                }

            }

            else{
                return 2;
            }
        }

    }
    return 2;
}

bool Database::Create_DB(){

    // Create Database Tables :

    QString my_query;
    bool result;
    QSqlQuery query;

    my_query = "CREATE TABLE Customers ( "
               "\"Customer ID\"     SERIAL, "
               "  Firstname         varchar(50) not null, "
               "  Lastname          varchar(50) not null, "
               "  Email             varchar(70) not null, "
               "\"Phone number\"	varchar(15), "
               "\"Mobile number\"   varchar(20) not null, "
               "  Address           text, "
               "  city              varchar(30), "
               "\"Postal code\"     varchar(15), "
               "  birthdate         date, "
               "  Wallet            int, "
               "  Attachments       bytea, "
               "  Username          varchar(40) not null, "
               "  primary key(\"Customer ID\") "
               ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Employee ( "
               "\"Employee ID\"     SERIAL, "
               "Firstname           varchar(50) not null, "
               "Lastname            varchar(50) not null, "
               "\"National ID\"     varchar(12) not null, "
               "Email               varchar(70) not null, "
               "\"Phone number\"	varchar(15), "
               "\"Mobile number\"	varchar(20) not null,"
               "Address             text,"
               "city                varchar(30), "
               "\"Postal code\"     varchar(15), "
               "birthdate           date, "
               "Attachments         bytea, "
               "Username            varchar(40) not null, "
               "primary key(\"Employee ID\") "
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Suppliers( "
               "\"Supplier ID\"     SERIAL, "
                "\"Company name\"	varchar(30) not null, "
                "Email              varchar(70) not null, "
                "Phone              varchar(20), "
                "\"Company Type\"	varchar(30) not null, "
                "Attachments        bytea, "
                "primary key(\"Supplier ID\") "
            ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());


    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Cart( "
               "\"Cart ID\"         SERIAL, "
               "\"Customer ID\"     integer not null, "
               "\"Total price\"     integer not null, "
               "\"Pay status\"      integer not null, "
               "primary key(\"Cart ID\"), "
               "foreign key(\"Customer ID\") references Customers "
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Products( "
               "\"Product ID\"      SERIAL, "
               "\"Supplier ID\"     integer not null, "
               "\"Product name\"	varchar(40) not null, "
               "Category            varchar(30) not null, "
               "\"Unit cost\"       integer not null, "
               "Stock               integer not null, "
               "primary key(\"Product ID\"), "
               "foreign key(\"Supplier ID\") references Suppliers "
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Product_PIC( "
            "ID                     SERIAL, "
            "\"Product ID\"         integer not null, "
            "Attachments            bytea not null, "
            "primary                key(ID),"
            "foreign key(\"Product ID\") references Products "
        ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Cart_item( "
               "\"Cart ID\"         integer not null, "
               "\"Product ID\"      integer not null, "
               "Quantity            integer not null, "
               "\"Unit cost\"       integer not null, "
               "primary key(\"Cart ID\",\"Product ID\"), "
               "foreign key(\"Cart ID\") references Cart, "
               "foreign key(\"Product ID\") references Products "
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Transactions( "
               "\"Transaction ID\"      SERIAL, "
               "\"Customer ID\"         integer not null, "
               "\"Transaction type\"	varchar(20) not null, "
               "\"Transaction amount\"	integer not null, "
               "\"Transaction status\"	varchar(20) not null, "
               "primary key(\"Transaction ID\"), "
               "foreign key(\"Customer ID\") references Customers "
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Favorites( "
               "\"Customer ID\"     integer, "
               "\"Product ID\"      integer, "
               "primary key(\"Customer ID\",\"Product ID\"), "
               "foreign key(\"Customer ID\") references Customers, "
               "foreign key(\"Product ID\") references Products"
           ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    my_query = "CREATE TABLE Account( "
               "Username            varchar(30) not null, "
               "\"Password\"        varchar(40) not null, "
               "\"Account type\"	integer not null, "
               "primary key(Username) "
            ");\n "; // OK

    result = query.exec(my_query.toUtf8().constData());

    if (result == false){
        return false;
    }

    query.clear();

    return true;
}

void Database::Disconnect(){
    DB.close();
}

bool Database::Execute(QString& qry,QSqlQuery& query){

    if(qry.isEmpty()){
        return query.exec();
    }
    else{
        //QSqlQuery query;
        return query.exec(qry);
    }
}

bool Database::IsConnected(){
    return DB.isOpen();
}

