#ifndef WIDGET_FOR_USER_H
#define WIDGET_FOR_USER_H

#include <QTabWidget>
namespace Ui {
class Widget_For_User;
}

class Widget_For_User : public QTabWidget
{
    Q_OBJECT

public:
    explicit Widget_For_User(QTabWidget *parent = 0);
    ~Widget_For_User();

private slots:
    void login(QString name);
signals:
    void init();
private:
    Ui::Widget_For_User *ui;
};

#endif // WIDGET_FOR_USER_H
