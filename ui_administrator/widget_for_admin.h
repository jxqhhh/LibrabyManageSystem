#ifndef WIDGET_FOR_ADMIN_H
#define WIDGET_FOR_ADMIN_H

#include <QTabWidget>
#include "utilTool/QStringLiteral.h"

namespace Ui {
    class Widget_For_Admin;
}

class Widget_For_Admin : public QTabWidget
{
    Q_OBJECT

public:
    explicit Widget_For_Admin(QTabWidget *parent = 0);
    ~Widget_For_Admin();

signals:
    void init();
private slots:
    void login(QString name);
private:
    Ui::Widget_For_Admin *ui;
};

#endif // WIDGET_FOR_ADMIN_H
