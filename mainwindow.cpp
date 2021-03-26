#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("test");
     db.setUserName("root");
     db.setPassword("");
     if(db.open()){
         ui->label->setText("connected:");
     }
     else{
          ui->label->setText("NOT connected:");
     }
       QSqlQuery query(db);
//     query.prepare("CREATE TABLE IF NOT EXISTS users ("
//             "email varchar(50) NOT NULL, password varchar(50) NOT NULL, username VARCHAR(50) NOT NULL, id int(11) NOT NULL AUTO_INCREMENT, "
//             "PRIMARY KEY(id))");
//             if(query.exec())
//                 {
//                     ui->label->setText("Table user created");
//                 }
//             else{
//                    ui->label_2->setText("Table hocreated");
//             }
//             //
//     query.prepare("CREATE TABLE IF NOT EXISTS Catalog ("
//                   "id INT NOT NULL, list_no INT NOT NULL, list_name VARCHAR(50) NOT NULL, time DATE NOT NULL,"
//                   "PRIMARY KEY(list_no));");
//             if(query.exec())
//                 {
//                     ui->label_2->setText("Table cata created");
//                 }
//             else{
//                    ui->label_2->setText("Table hocreated");
//                     }
//     query.prepare("CREATE TABLE IF NOT EXISTS List ("
//                   "list_no INT NOT NULL, item_no INT NOT NULL, item_name VARCHAR(50) NOT NULL,"
//                   "PRIMARY KEY(item_no));");
//             if(query.exec())
//                 {
//                     ui->label_2->setText("Table list created");
//                 }
//             else{
//                    ui->label_2->setText("Table hocreated");

//             }

}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_userInput->text();
    QString password = ui->lineEdit_passInput->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("test");
     db.setUserName("root");
     db.setPassword("");
     if(db.open()){
         ui->label->setText("connected:");
     }
     else{
          ui->label->setText("NOT connected:");
     }
     QSqlQuery query(db);
     bool userlogined=false;
     QString q="SELECT * FROM users WHERE users username = "+username;
     qDebug()<<q;
    query.exec("SELECT * FROM users");
    while (query.next()) {
            QString usernamedb = query.value(2).toString();
            QString passdb = query.value(1).toString();
            if(username==usernamedb && password==passdb){
                QMessageBox::information(this, "Login", "You are login!!");
                userlogined=true;
                close();
                QString Iduser= query.value(3).toString();
                secondMain secondMain;
                secondMain.setModal(true);
                secondMain.exec();
                break;
            }


        }
    if(userlogined==false){
        QMessageBox::warning(this,"Login","Username or password is not correct");

    }


}
