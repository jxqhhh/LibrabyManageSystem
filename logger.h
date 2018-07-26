#ifndef LOGGER_H
#define LOGGER_H
#include <QWidget>
#include <QMainWindow>
#include "ui_administrator/widget_for_admin.h"

#include "utilTool/sqlfunction.h"
//登录界面

namespace Ui {
class logger;
}

class logger : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindow;
    explicit logger(QWidget *parent = 0);
    ~logger();
    QString get_name();
    //new_account_apply* n;
    void initialize();
private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
    void reshow();
    void on_pushButton_exit_clicked();
    void on_pushButton_connect_clicked();
    void enter();
private:
    Ui::logger *ui;
signals:
    void log_valid_user(QString name);
    void log_valid_admin(QString name);
};

#endif // LOGGER_H
