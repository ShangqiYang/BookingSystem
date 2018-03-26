#include "admininfo.h"
#include "ui_admininfo.h"
#include "addschedule.h"
#include "delete_schedule.h"

admininfo::admininfo(QWidget *parent):
    QDialog(parent),
    ui(new Ui::admininfo)
{
    ui->setupUi(this);
    if(!connOpen())
        ui->label_databaseConn->setText("Failed to open the database!");
    else
        ui->label_databaseConn->setText("Connected.....");
    Display();
}

admininfo::~admininfo()
{
    delete ui;
}

//display the schedule on the screen
void admininfo::Display(){

    QSqlQueryModel *modal=new QSqlQueryModel();
    qry=new QSqlQuery(mydb);
    qry->prepare("select * from DataInfo");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
    delete qry;
}

//connect to the database
bool admininfo::connOpen(){
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

void admininfo::connClose(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}
//add time slots into the schedule
void admininfo::on_pushButton_add_clicked()
{
    addschedule Addschedule;
    Addschedule.setModal(true);
    Addschedule.exec();
    Display();

}
//delete time slots into the schedule
void admininfo::on_pushButton_delete_clicked()
{   delete_schedule Delete_schedule;
    Delete_schedule.setModal(true);
    Delete_schedule.exec();
    Display();

}
