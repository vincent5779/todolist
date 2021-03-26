#ifndef THIRDMAIN_H
#define THIRDMAIN_H

#include <QDialog>
#include"secondmain.h"
namespace Ui {
class thirdmain;
}

class thirdmain : public QDialog
{
    Q_OBJECT

public:
    explicit thirdmain(QWidget *parent = nullptr);
    ~thirdmain();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::thirdmain *ui;
};

#endif // THIRDMAIN_H
