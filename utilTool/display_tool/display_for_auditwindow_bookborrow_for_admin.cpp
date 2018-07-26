#include "display_for_auditwindow_bookborrow_for_admin.h"
#include "ui_administrator/auditwindow_for_admin.h"
#include <QDir>
#include <QCoreApplication>
display_for_auditwindow_bookborrow_for_admin::display_for_auditwindow_bookborrow_for_admin()
{

}

void display_for_auditwindow_bookborrow_for_admin::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    AuditWindow_For_Admin* w=dynamic_cast<AuditWindow_For_Admin*>(window);
    if(w==nullptr){return;}
    //释放之前的new出来的QPushButton
    for(int i=0;i<w->btn_vec_book_borrow_application_table.size();i++){
        delete w->btn_vec_book_borrow_application_table[i];
    }
    w->btn_vec_book_borrow_application_table.clear();
    //在table中加载出数据但不加载按钮
    QStringList btn_name;
    btn_name<<QStringLiteral("同意");
    btn_name<<QStringLiteral("拒绝");
    this->display_data_linear_without_btn(data,table,2,btn_name);
    //加载按钮
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QIcon acceptbtn_ico("image//iamge_for_ui_admin//auditwindow_for_admin//accept_application.png");
    QIcon rejectbtn_ico("image//iamge_for_ui_admin//auditwindow_for_admin//reject_application.png");
    int data_row_num=data->get_row_num();
    for(int i=0;i<data_row_num;i++){
        QPushButton *acceptBtn = new QPushButton();
        acceptBtn->setMinimumSize(40,30);
        acceptBtn->setMaximumSize(40,30);
        acceptBtn->setIcon(acceptbtn_ico);
        acceptBtn->setIconSize(QSize(28,28));
        QPushButton* rejectBtn = new QPushButton();
        rejectBtn->setMinimumSize(40,30);
        rejectBtn->setMaximumSize(40,30);
        rejectBtn->setIcon(rejectbtn_ico);
        rejectBtn->setIconSize(QSize(28,28));
        table->setCellWidget(i,0,acceptBtn);
        table->setCellWidget(i,1,rejectBtn);
        //关联信号与槽
        QObject::connect(acceptBtn,SIGNAL(clicked()),window,SLOT(accept_application()));
        QObject::connect(rejectBtn,SIGNAL(clicked()),window,SLOT(reject_application()));
        //保存指向new出来的QPushButton的指针，方便之后刷新页面时释放对应内存
        w->btn_vec_book_borrow_application_table.push_back(acceptBtn);
        w->btn_vec_book_borrow_application_table.push_back(rejectBtn);
    }
}

display_for_auditwindow_bookborrow_for_admin& display_for_auditwindow_bookborrow_for_admin::instance(){
    static display_for_auditwindow_bookborrow_for_admin d;
    return d;
}
