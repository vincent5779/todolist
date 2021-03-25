#include "secondmain.h"
#include "ui_secondmain.h"
#include<QMessageBox>
#include <QInputDialog>
#include <QDebug>

secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{
    ui->setupUi(this);
//    ui->label_userdb->setText(userN);

}

secondMain::~secondMain()
{
    delete ui;
}
//create new todo list
void secondMain::on_pushButton_clicked()
{
    bool ok;
       QString catalogI = QInputDialog::getText(this, tr("Wellcome to create new datalog: "),
                                               tr("Input the catalog name:"), QLineEdit::Normal,
                                               tr("none"), &ok);
          if (ok && !catalogI.isEmpty()){
              qDebug() << catalogI;
          }
       //add list to the this catalog or


}

void secondMain::on_pushButton_2_clicked()
{
        QMessageBox::information(this, "Show the data", "There are all the data");

}


void secondMain::on_pushButton_3_clicked()
{
    close();
}



void secondMain::on_label_3_linkActivated(const QString &link)
{

}
