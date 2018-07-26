#ifndef DISPLAYFUNCTION_H
#define DISPLAYFUNCTION_H
#include <QTableWidget>
#include <QString>
#include <QObject>
#include "utilTool/data_linear.h"
#include <QMainWindow>
#include <QTableWidget>

#include "utilTool/QStringLiteral.h"
class DisplayFunction:public QObject
{
    Q_OBJECT
protected:
    void display_data_linear_without_btn(data_linear* data,QTableWidget* table,int btn_num,QStringList btn_name);//在table中加载出数据但不加载按钮
public:
    //静态方法
    static void display_information(QString content, QTableWidget* table);
    static void information(QString head, QString cause, QWidget* window);//内容，原因/行为
    static int question(QString head, QString question, QWidget* window);
    static void normal(QTableWidget* table);
    virtual void display(data_linear* data,QTableWidget* table,QMainWindow *window)=0;
};
#endif // DISPLAYFUNCTION_H
