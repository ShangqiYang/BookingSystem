#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "studentinfo.h"
#include "admininfo.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT


public:

public:
    explicit login(QWidget *parent = 0);

    ~login();

     QSqlDatabase mydb;

     void connClose();

     bool connOpen();



private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    QSqlQuery* qry;


};

#endif // LOGIN_H
