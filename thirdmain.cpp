#include "thirdmain.h"
#include "ui_thirdmain.h"
#include"secondmain.h"

thirdmain::thirdmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdmain)
{
    ui->setupUi(this);
}

thirdmain::~thirdmain()
{
    delete ui;
}

void thirdmain::on_pushButton_3_clicked()
{
    close();
    secondMain secondMain;
    secondMain.setModal(true);
    secondMain.exec();
}
