#include "display_for_auditwindow_bookreturn_for_admin.h"
#include "ui_administrator/auditwindow_for_admin.h"
#include <QDir>
#include <QCoreApplication>
display_for_auditwindow_bookreturn_for_admin::display_for_auditwindow_bookreturn_for_admin()
{

}

void display_for_auditwindow_bookreturn_for_admin::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    AuditWindow_For_Admin* w=dynamic_cast<AuditWindow_For_Admin*>(window);
    if(w==nullptr){return;}
    //释放之前的new出来的QPushButton
    for(int i=0;i<w->btn_vec_book_unreturned_table.size();i++){
        delete w->btn_vec_book_unreturned_table[i];
    }
    w->btn_vec_book_unreturned_table.clear();
    //在table中加载出数据但不加载按钮
    QStringList btn_name;
    btn_name<<QStringLiteral("归还");
    display_data_linear_without_btn(data,table,1,btn_name);
    //加载按钮
    QIcon returnbtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//iamge_for_ui_admin//auditwindow_for_admin//book_return.png");
    int data_row_num=data->get_row_num();
    for(int i=0;i<data_row_num;i++){
        QPushButton *returnBtn = new QPushButton();
        returnBtn->setMinimumSize(40,30);
        returnBtn->setMaximumSize(40,30);
        returnBtn->setIcon(returnbtn_ico);
        returnBtn->setIconSize(QSize(28,28));
        table->setCellWidget(i,0,returnBtn);
        //关联信号与槽
        QObject::connect(returnBtn,SIGNAL(clicked()),window,SLOT(return_book()));
        //保存指向new出来的QPushButton的指针，方便之后刷新页面时释放对应内存
        w->btn_vec_book_unreturned_table.push_back(returnBtn);
    }
}

display_for_auditwindow_bookreturn_for_admin& display_for_auditwindow_bookreturn_for_admin::instance(){
    static display_for_auditwindow_bookreturn_for_admin d;
    return d;
}
