#include "studentinfo.h"
#include "ui_studentinfo.h"
#include "changpassword.h"
#include <QMessageBox>

studentinfo::studentinfo(QString Name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentinfo)
{
    ui->setupUi(this);
    Username=Name;
    if(!connOpen())
        ui->label_stu_status->setText("Failed to open the database!");
    else
        ui->label_stu_status->setText("Connected.....");

    // show the name of student
    ui->label_name->setText(Name);

    // display the status of booking
    displaysBookingStatus();

    // display the date that is available for book
    display_main();


}

studentinfo::~studentinfo()
{
    delete ui;
}
// connect to the database
bool studentinfo::connOpen(){
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
// close the database;
void studentinfo::connClose(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}

// show the status with the username and booked time
void studentinfo::displaysBookingStatus(){

    qry=new QSqlQuery(mydb);
    qry->prepare("select * from LoginInfo where name='"+Username+"'");


    if(qry->exec()){
        while(qry->next())
        {
            ui->label_bookingstatus->setText(qry->value(3).toString());
            ui->label_Time->setText(qry->value(4).toString());
            weekDay=qry->value(3).toString();

        }
    }
}

// cancel the appointment
void studentinfo::CancelBookingStatus(){
    QString ava="1";\
    QString temp="";

    qry=new QSqlQuery(mydb);
    qry->prepare("update DataInfo set PersonBook='"+temp+"'where Weekday='"+weekDay+"'");
    qry->exec();
    delete qry;

    qry=new QSqlQuery(mydb);
    qry->prepare("update DataInfo set Available='"+ava+"'where Weekday='"+weekDay+"'");
    qry->exec();
    delete qry;

    qry=new QSqlQuery(mydb);
    qry->prepare("update LoginInfo set appointmentDate='"+temp+"'where name='"+Username+"'");
    qry->exec();
    delete qry;

    qry=new QSqlQuery(mydb);
    qry->prepare("update LoginInfo set AppointmentTime='"+temp+"'where name='"+Username+"'");
    qry->exec();
    delete qry;

    qry=new QSqlQuery(mydb);
    qry->prepare("update LoginInfo set availableBook='true'where name='"+Username+"'");
    qry->exec();
    delete qry;

    QMessageBox::warning(this,tr("Attention"),tr("Successful cancel!"));


}

// save the booked time and store it in the database
void studentinfo::updateBookingStatus(){

    weekDay=ui->comboBox_weekday->currentText();
    QString BeginTime=ui->comboBox_time->currentText();
    QString EndTime=ui->label_endtime->text();
    QString ava="0";
    qry=new QSqlQuery(mydb);
    qry->prepare("update DataInfo set PersonBook='"+Username+"'where Weekday='"+weekDay+"'and BeginTime='"+BeginTime+"' and EndTime='"+EndTime+"'");
    qry->exec();
    delete qry;

    qry=new QSqlQuery(mydb);
    qry->prepare("update DataInfo set Available='"+ava+"'where Weekday='"+weekDay+"'and BeginTime='"+BeginTime+"' and EndTime='"+EndTime+"'");
    qry->exec();
    delete qry;

}

// display the available appointment on the board
void studentinfo::display_main(){
        QSqlQueryModel *modal=new QSqlQueryModel();
        qry=new QSqlQuery(mydb);
        QString ava1="1";
        qry->prepare("select Weekday,BeginTime,EndTime from DataInfo where Available='"+ava1+"'");

        qry->exec();
        modal->setQuery(*qry);

        ui->tableView->setModel(modal);
        qDebug()<<(modal->rowCount());


// display the time that can be booked
        modal=new QSqlQueryModel();
        qry=new QSqlQuery(mydb);
        qry->prepare("select Weekday from DataInfo where Available='"+ava1+"'");

        qry->exec();
        modal->setQuery(*qry);

        ui->comboBox_weekday->setModel(modal);

        qDebug()<<(modal->rowCount());
}


void studentinfo::on_pushButton_booking_clicked()
{
    QString temp;
    qry=new QSqlQuery(mydb);
    qry->prepare("select PersonBook from DataInfo");
    qry->exec();
    if(qry->next())
     {
         if(qry->value(0).toString()==Username){
             QMessageBox::warning(this,tr("Attention"),tr("You have already book for an apointment,if you want to change the sechedule,you need to cancel it first!"));
         }else{
             updateLoginInfo();
             display_main();
         }
     }
}

// update the status of appointments
void studentinfo::updateLoginInfo(){


    qry=new QSqlQuery(mydb);
    weekDay=ui->comboBox_weekday->currentText();
    QString BeginTime=ui->comboBox_time->currentText();
    QString EndTime=ui->label_endtime->text();
    QString AppointmentData=weekDay;
    QString AppointmentTime=BeginTime+"--"+EndTime;

    qry->prepare("update LoginInfo set appointmentDate='"+AppointmentData+"'where name='"+Username+"'");
    qry->exec();


    qry=new QSqlQuery(mydb);
    qry->prepare("update LoginInfo set AppointmentTime='"+AppointmentTime+"'where name='"+Username+"'");
    qry->exec();

    qry=new QSqlQuery(mydb);
    qry->prepare("update LoginInfo set availableBook='false'where name='"+Username+"'");
    if(qry->exec())
     {
         QMessageBox::information(this,tr("Booking"),tr("Your booking has saved"));
     }

    displaysBookingStatus();
    updateBookingStatus();

}

// update the weekday
void studentinfo::on_comboBox_weekday_currentIndexChanged(const QString &arg1)
{
    QSqlQueryModel *modal=new QSqlQueryModel();
    QString Weekday=ui->comboBox_weekday->currentText();
    modal=new QSqlQueryModel();
    qry=new QSqlQuery(mydb);
    qry->prepare("select BeginTime from DataInfo where Weekday='"+Weekday+"'");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_time->setModel(modal);
    qDebug()<<(modal->rowCount());

}

void studentinfo::on_pushButton_2_clicked()
{
    CancelBookingStatus();
    displaysBookingStatus();
    display_main();

}

// update the daytime
void studentinfo::on_comboBox_time_currentIndexChanged(const QString &arg1)
{
    QString Weekday=ui->comboBox_weekday->currentText();
    QString BeginTime=ui->comboBox_time->currentText();
    qry=new QSqlQuery(mydb);
    qry->prepare("select * from DataInfo where Weekday='"+Weekday+"' and BeginTime='"+BeginTime+"'");
    qry->exec();
    if(qry->first()){
    ui->label_endtime->setText(qry->value(2).toString());
}

}

// change password
void studentinfo::on_pushButton_resetPW_clicked()
{
    connClose();
    ChangPassword changpassword(Username);
    changpassword.setModal(true);
    changpassword.exec();
}
