#ifndef CHANGPASSWORD_H
#define CHANGPASSWORD_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ChangPassword;
}

class ChangPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangPassword(QString username,QWidget *parent = 0);
    ~ChangPassword();

private slots:
    void on_pushButton_clicked();

    bool connOpen();

    void connClose();

private:
    Ui::ChangPassword *ui;
    QSqlQuery* qry;
    QSqlDatabase mydb;
    QString Username;
};

#endif // CHANGPASSWORD_H
