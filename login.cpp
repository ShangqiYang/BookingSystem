<<<<<<< HEAD
#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //set the logo on the left hand
    QPixmap pix("C:/Users/Tesla.L/Desktop/login.png");
    ui->label_pic->setPixmap((pix));

    //whether the database is open or not
    if(!connOpen())
        ui->label->setText("Failed to open the database!");
    else
        ui->label->setText("Connected.....");
}

login::~login()
{
    delete ui;

}

void login::on_pushButton_clicked()
{
    //for the user to login to the booking system
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    qry=new QSqlQuery(mydb);
    qry->prepare("select name from LoginInfo where username='"+username+"' and password='"+password+"'");

    if(qry->exec())

    {
        int count=0;
        while(qry->next()){
            //if the user is professor , the system will enter as an admin.
            count++;
            if(count==1&&QString::compare(ui->lineEdit_username->text(),"admin")==0){
               if(QString::compare(ui->lineEdit_password->text(),"123456")==0){
                    this->hide();
                    connClose();
                    admininfo Admininfo;
                    Admininfo.setModal(true);
                    Admininfo.exec();
                }
            }else if(count==1){

                // the user will login as a student.
                ui->label->setText("username and password is correct");
                this->hide();
                QString Name=qry->value(0).toString();
                connClose();
                studentinfo Studentinfo(Name);
                Studentinfo.setModal(true);
                Studentinfo.exec();
            }
          }
            if(count<1)
               QMessageBox::warning(this,tr("Fail to login"),tr("Id or password is incorrect!"));

    }

}

void login::connClose()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool login::connOpen(){

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
=======
#include "Students.h"
class login {
private:
	unordered_map<string, string>id_password;
public:
	//read a text file and store the data of student's Id with it's password in a map called id_password;
	login() {
		ifstream file("login.txt");
		string line;
		while (getline(file, line)) {
			istringstream ss(line);
			string a;
			string b;
			bool p = true;
			while (getline(ss, a, '\t')) {
				cout << a << endl;
				if (p) {
					b = a;
					p = false;
				}
				id_password[b] = a;
			}
		}
		file.close();
		/*for (map<string, string>::iterator it = id_password.begin(); it != id_password.end(); it++) {
			cout << "student_id:" << it->first << '\t' << "password:" << it->second << endl;
		}*/
	}
	//match the input id and password with data which stored in map 
	void search(const string& id, const string& password) {
		bool id_temp = false;
		bool pass_temp = false;
		bool Teacher = false;
			for (unordered_map<string, string>::iterator it = id_password.begin(); it != id_password.end(); it++) {
				if (id == it->first) {
					id_temp = true;
					if (password == it->second) {
						pass_temp = true;
						if (it == id_password.begin()) {
							Teacher = true;
						}
					}
				}
			}
			//Judge whether the individual is profressor or student, then making or cancelling an appointment
			if (id_temp&&pass_temp) {
				if (Teacher) {
					cout << "Welcome Prof" << endl;
					//call the class for the profressor.
					teacher obj;
					int i;
					do {
						cout << "1.Setup time for appointment." << endl;
						cout << "2.Display the time for appintment." << endl;
						cout << "3.Cancel the appointment" << endl;
						cout << "0.log out!" << endl;
						cin >> i;
						switch (i)
						{
						case 1: obj.setup();
							obj.readin();
							break;
						case 2: obj.display();
							break;
						case 3:/*a.cancel();*/
							break;
						case 0:
							break;
						}
					} while (i != 0);
				}
				else {
					cout << "Welcome student!!" << endl;
					students stu;
					int i;
					do {
						cout << "1.booking time for appointment." << endl;
						cout << "2.Display the time for appintment." << endl;
						cout << "3.Cancel the appointment" << endl;
						cout << "0.log out!" << endl;
						cin >> i;
						switch (i)
						{
						case 1:stu.booking();
							break;
						case 2: stu.display();
							break;
						case 3:/*a.cancel();*/
							break;
						case 0:
							break;
						}
					} while (i != 0);
				}
			}
			else {
				cout << "your id or password is wrong! Please try again!!" << endl;
			}
	}
	

	void Login_temp() {
		while (true) {
			string a, b;
			cout << "Please enter your id:";
			cin >> a;
			cout << "Please enter your password:";
			cin >> b;
			cin.sync();
			search(a, b);
		}
	}
	
};


int main() {
	login login;
	login.Login_temp();
	return 0;
}
