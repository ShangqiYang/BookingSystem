#include "changpassword.h"
#include "ui_changpassword.h"
#include <QMessageBox>

ChangPassword::ChangPassword(QString username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangPassword)
{
    ui->setupUi(this);
    Username=username;
    connOpen();
}

ChangPassword::~ChangPassword()
{
    delete ui;
}

//connect to the database
bool ChangPassword::connOpen(){
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

void ChangPassword::connClose(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}

// change password by entering correct old password
void ChangPassword::on_pushButton_clicked()
{
    QString oldpassword,newpassword,Confpassword;
    oldpassword=ui->lineEdit_pw->text();
    newpassword=ui->lineEdit_Npw->text();
    Confpassword=ui->lineEdit_cnpw->text();
    qry=new QSqlQuery(mydb);
    qry->prepare("select password from LoginInfo where name='"+Username+"'");

    if(qry->exec()){
    while(qry->next()){
        if(qry->value(0).toString()!=oldpassword){
            QMessageBox::warning(this,tr("Warning"),tr("Old password is wrong!"));
        }else{
            if(Confpassword==newpassword){
                QSqlQuery* qry1;
                QMessageBox::information(this,tr("GOOD Gob!"),tr("Successful change the password!"));
                qry1=new QSqlQuery(mydb);
                qry1->prepare("update LoginInfo set password='"+newpassword+"'where name='"+Username+"'");
                qry1->exec();
                this->hide();
                // confirm the new password
            }else{
                QMessageBox::warning(this,tr("Warning"),tr("Please enter the same password!"));
            }
        }
     }
  }
}
