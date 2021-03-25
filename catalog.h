#ifndef CATALOG_H
#define CATALOG_H

#include <QWidget>

namespace Ui {
class catalog;
}

class catalog : public QWidget
{
    Q_OBJECT

public:
    explicit catalog(QWidget *parent = nullptr);
    ~catalog();

private:
    Ui::catalog *ui;
};

#endif // CATALOG_H
