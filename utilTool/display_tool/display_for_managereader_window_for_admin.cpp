#include "display_for_managereader_window_for_admin.h"
#include "ui_administrator/managereaderwindow_for_admin.h"
#include <QDir>
#include <QCoreApplication>
#include "utilTool/QStringLiteral.h"
display_for_managereaderwindow_for_admin::display_for_managereaderwindow_for_admin(){

}

void display_for_managereaderwindow_for_admin::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    ManageReaderWindow_For_Admin* w=dynamic_cast<ManageReaderWindow_For_Admin*>(window);
    if(w==nullptr){return;}
    //释放之前的new出来的QPushButton
    for(int i=0;i<w->btn_vec.size();i++){
        delete w->btn_vec[i];
    }
    w->btn_vec.clear();
    //在table中加载出数据但不加载按钮
    QStringList btn_name;
    btn_name<<QStringLiteral("删除");
    display_data_linear_without_btn(data,table,1,btn_name);
    //加载按钮
    QIcon btn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//iamge_for_ui_admin//managereaderwindow_for_admin//delete_reader.png");
    int data_row_num=data->get_row_num();
    for(int i=0;i<data_row_num;i++){
        QPushButton *Btn = new QPushButton();
        Btn->setMinimumSize(40,30);
        Btn->setMaximumSize(40,30);
        Btn->setIcon(btn_ico);
        Btn->setIconSize(QSize(28,28));
        table->setCellWidget(i,0,Btn);
        //关联信号与槽
        QObject::connect(Btn,SIGNAL(clicked()),window,SLOT(delete_reader()));
        //保存指向new出来的QPushButton的指针，方便之后刷新页面时释放对应内存
        w->btn_vec.push_back(Btn);
    }
}

display_for_managereaderwindow_for_admin& display_for_managereaderwindow_for_admin::instance(){
    static display_for_managereaderwindow_for_admin d;
    return d;
}
