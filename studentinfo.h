#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include "login.h"

namespace Ui {
class studentinfo;
}

class studentinfo : public QDialog
{
    Q_OBJECT

public:
    explicit studentinfo(QString Username,QWidget *parent = 0);

    ~studentinfo();

private slots:

    void on_pushButton_booking_clicked();

    void on_comboBox_weekday_currentIndexChanged(const QString &arg1);

    void displaysBookingStatus();

    void updateBookingStatus();

    void CancelBookingStatus();

    void updateLoginInfo();

    void display_main();

    void on_pushButton_2_clicked();

    void connClose();

    bool connOpen();

    void on_comboBox_time_currentIndexChanged(const QString &arg1);

    void on_pushButton_resetPW_clicked();

private:
    Ui::studentinfo *ui;
    QSqlQuery* qry;
    QSqlDatabase mydb;
    QString Username;
    QString weekDay;
};

#endif // STUDENTINFO_H
