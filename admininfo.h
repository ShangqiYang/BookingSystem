#ifndef ADMININFO_H
#define ADMININFO_H

#include <QDialog>
#include "login.h"

namespace Ui {
class admininfo;
}

class admininfo : public QDialog{

    Q_OBJECT

public:
    explicit admininfo(QWidget *parent = 0);
    ~admininfo();
    void Display();

private slots:

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    bool connOpen();

    void connClose();

private:

    Ui::admininfo *ui;
    QSqlQuery* qry;
    QSqlDatabase mydb;
};

#endif // ADMININFO_H
