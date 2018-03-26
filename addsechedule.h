#ifndef ADDSECHEDULE_H
#define ADDSECHEDULE_H

#include <QDialog>
#include "login.h"
namespace Ui {
class addsechedule;
}

class addsechedule : public QDialog
{
    Q_OBJECT

public:
    explicit addsechedule(QWidget *parent = 0);

    ~addsechedule();

    void AddNewSechedule();

    bool connOpen();

    void connClose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addsechedule *ui;
    QSqlQuery* qry;
    QSqlDatabase mydb;
};

#endif // ADDSECHEDULE_H
