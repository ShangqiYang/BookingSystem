#ifndef DELETE_SCHEDULE_H
#define DELETE_SCHEDULE_H

#include <QDialog>
#include "login.h"

namespace Ui {
class delete_schedule;
}

class delete_schedule : public QDialog
{
    Q_OBJECT

public:
    explicit delete_schedule(QWidget *parent = 0);
    ~delete_schedule();

    void display();

    void delete_sech();

    bool connOpen();

    void connClose();

private slots:
    void on_comboBox_WeekDay_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_BeginTime_currentIndexChanged(const QString &arg1);

private:
    Ui::delete_schedule *ui;
    QSqlQuery* qry;
    QSqlDatabase mydb;
};

#endif // DELETE_SCHEDULE_H
