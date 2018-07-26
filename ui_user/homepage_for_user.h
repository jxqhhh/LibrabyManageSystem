#ifndef HOMEPAGE_FOR_USER_H
#define HOMEPAGE_FOR_USER_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include "utilTool/data_linear.h"
using std::vector;
namespace Ui {
class HomePage_For_User;
}

class HomePage_For_User : public QMainWindow
{
    Q_OBJECT
    data_linear* data;
public:
    explicit HomePage_For_User(QWidget *parent = 0);
    ~HomePage_For_User();

private slots:
    void load_latest_book();
private:
    Ui::HomePage_For_User *ui;
};

#endif // HOMEPAGE_FOR_USER_H
