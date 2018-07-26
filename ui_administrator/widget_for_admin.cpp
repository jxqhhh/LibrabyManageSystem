
#include "widget_for_admin.h"
#include "auditwindow_for_admin.h"
#include "managebookwindow_for_admin.h"
#include "managereaderwindow_for_admin.h"
#include <QLabel>
#include <QMainWindow>
#include <cstring>
#include "utilTool/sqlfunction.h"
#include "ui_widget_for_admin.h"
Widget_For_Admin::Widget_For_Admin(QTabWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Widget_For_Admin)
{
    AuditWindow_For_Admin *auditwindow=new AuditWindow_For_Admin();
    ManageBookWindow_For_Admin *ManageBook=new ManageBookWindow_For_Admin();
    ManageReaderWindow_For_Admin *ManageReader=new ManageReaderWindow_For_Admin();
    this->addTab(auditwindow,QStringLiteral("图书借还管理"));
    this->addTab(ManageBook,QStringLiteral("图书管理"));
    this->addTab(ManageReader,QStringLiteral("读者管理"));
    this->setTabPosition(QTabWidget::North);
    ui->setupUi(this);
    connect(this,SIGNAL(init()),ManageBook,SLOT(load_all_book()));

    connect(this,SIGNAL(init()),ManageReader,SLOT(load_all()));

    connect(this,SIGNAL(init()),auditwindow,SLOT(load_all()));
}

Widget_For_Admin::~Widget_For_Admin()
{
    delete ui;
}

void Widget_For_Admin::login(QString name){
    this->show();
    emit init();
}


