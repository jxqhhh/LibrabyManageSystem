
#include <QApplication>
#include <QDialog>
#include <QDebug>
#include <QObject>
#include "logger.h"
#include "ui_user/widget_for_user.h"
#include "ui_administrator/widget_for_admin.h"
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget_For_Admin w1;
    Widget_For_User w2;
    logger l;
    QObject::connect(&l,SIGNAL(log_valid_admin(QString)),&w1,SLOT(login(QString)));
    QObject::connect(&l,SIGNAL(log_valid_user(QString)),&w2,SLOT(login(QString)));

    l.show();
    return a.exec();
}
