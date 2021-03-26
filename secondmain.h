#ifndef SECONDMAIN_H
#define SECONDMAIN_H

#include <QDialog>
#include "thirdmain.h"

namespace Ui {
class secondMain;
}

class secondMain : public QDialog
{
    Q_OBJECT

public:
    explicit secondMain(QWidget *parent = nullptr);
    ~secondMain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_pushButton_3_clicked();



    void on_label_3_linkActivated(const QString &link);

private:
    Ui::secondMain *ui;

//    tasklist *Tasklist;
};

#endif // SECONDMAIN_H
