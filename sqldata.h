#ifndef SQLDATA_H
#define SQLDATA_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <vector>


struct appointment_data{
    QString weekday;
    QString BeginTime;
    QString EndTime;

};

class Sqldata
{
private:
    vector<appointment_data*> vec;
    appointment_data* data;
public:
    Sqldata();

    QSqlDatabase mydb;
    QSqlQuery* qry;

    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){

        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/Tesla.L/Desktop/StudentInfo.sqlite");

        if(!mydb.open()){
            qDebug()<<("Failed to open the database!");
            return false;
        }
        else{
            qDebug()<<("Connected.....");
            return true;
        }
    }
};

#endif // SQLDATA_H
