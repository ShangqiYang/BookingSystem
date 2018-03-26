#include "delete_schedule.h"
#include "ui_delete_schedule.h"
#include <QMessageBox>

delete_schedule::delete_schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_schedule)
{
    ui->setupUi(this);
    connOpen();
    display();
}

delete_schedule::~delete_schedule()
{
    delete ui;
}

//open the database
bool delete_schedule::connOpen(){
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

void delete_schedule::connClose(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

// display the schedule
void delete_schedule::display(){
    QSqlQueryModel* modal=new QSqlQueryModel();

    qry=new QSqlQuery(mydb);
    qry->prepare("select Weekday from DataInfo");

    qry->exec();
    modal->setQuery(*qry);

    ui->comboBox_WeekDay->setModel(modal);
    qDebug()<<(modal->rowCount());

    delete qry;


}

//change the index of combobox
void delete_schedule::on_comboBox_WeekDay_currentIndexChanged(const QString &arg1)
{
    QString Weekday=ui->comboBox_WeekDay->currentText();
    QSqlQueryModel* modal=new QSqlQueryModel();

    qry=new QSqlQuery(mydb);
    qry->prepare("select BeginTime from DataInfo where Weekday='"+Weekday+"'");

    qry->exec();
    modal->setQuery(*qry);

    ui->comboBox_BeginTime->setModel(modal);
    qDebug()<<(modal->rowCount());

    delete qry;
}

// delete the appointment
void delete_schedule::delete_sech(){

    QString temp="";
    qry=new QSqlQuery(mydb);
    QString weekDay=ui->comboBox_WeekDay->currentText();
    QString BeginTime=ui->comboBox_BeginTime->currentText();
    QString EndTime=ui->lineEdit_2->text();

    qry->prepare("select PersonBook from DataInfo where Weekday='"+weekDay+"'and BeginTime='"+BeginTime+"'and EndTime='"+EndTime+"'");
    qry->exec();
    //delete the time slot which has not been booked
    if(qry->first()){
        if(qry->value(0).toString()==""){
            qry=new QSqlQuery(mydb);
            qry->prepare("delete from DataInfo where Weekday='"+weekDay+"'and BeginTime='"+BeginTime+"'and EndTime='"+EndTime+"'");
            qry->exec();
            delete qry;
        // delete the time slot which has already been booked
        }else{

            QString person=qry->value(0).toString();
            QMessageBox::StandardButton reply;
            reply=QMessageBox::warning(this,tr("warning"),tr("This DATA had been booked,if you cancel it, it will send the email to the student."),
                                        QMessageBox::Yes | QMessageBox::No);
            if(reply==QMessageBox::Yes)
            {
            qry=new QSqlQuery(mydb);
            qry->prepare("delete from DataInfo where Weekday='"+weekDay+"'and BeginTime='"+BeginTime+"'and EndTime='"+EndTime+"'");
            qry->exec();
            delete qry;

            qry=new QSqlQuery(mydb);
            qry->prepare("update LoginInfo set appointmentDate='"+temp+"'where name='"+person+"'");
            qry->exec();
            delete qry;

            qry=new QSqlQuery(mydb);
            qry->prepare("update LoginInfo set AppointmentTime='"+temp+"'where name='"+person+"'");
            qry->exec();
            delete qry;

            qry=new QSqlQuery(mydb);
            qry->prepare("update LoginInfo set availableBook='true'where name='"+person+"'");
            qry->exec();
            delete qry;
            }

        }
    }
    delete qry;
}

void delete_schedule::on_pushButton_clicked()
{
    delete_sech();
    this->hide();
}

void delete_schedule::on_comboBox_BeginTime_currentIndexChanged(const QString &arg1)
{   QString weekDay=ui->comboBox_WeekDay->currentText();
    QString BeginTime=ui->comboBox_BeginTime->currentText();
    qry=new QSqlQuery(mydb);
    qry->prepare("select EndTime from DataInfo where Weekday='"+weekDay+"' and BeginTime='"+BeginTime+"'");

    if(qry->exec()){
        while(qry->next())
        {
            ui->lineEdit_2->setText(qry->value(0).toString());
        }
    }
    delete qry;
}
