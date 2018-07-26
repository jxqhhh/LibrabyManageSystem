#include "display_for_managebookwindow_for_admin.h"
#include "ui_administrator/managebookwindow_for_admin.h"
#include <QDir>
#include <QCoreApplication>
display_for_managebookwindow_for_admin::display_for_managebookwindow_for_admin()
{

}

void display_for_managebookwindow_for_admin::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    ManageBookWindow_For_Admin* w=dynamic_cast<ManageBookWindow_For_Admin*>(window);
    if(w==nullptr){
        return;
    }
    //释放之前的new出来的QPushButton
    for(int i=0;i<w->btn_vec.size();i++){
        delete w->btn_vec[i];
    }
    w->btn_vec.clear();
    //在table中加载出数据但不加载按钮
    QStringList btn_name;
    btn_name<<QStringLiteral("预览");
    btn_name<<QStringLiteral("修改");
    btn_name<<QStringLiteral("删除");
    display_data_linear_without_btn(data,table,3,btn_name);
    //加载按钮
    QIcon changebtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//iamge_for_ui_admin//managebookwindow_for_admin//change_book_info.png");
    QIcon delbtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//iamge_for_ui_admin//managebookwindow_for_admin//delete_book.png");
    QIcon previewbtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//iamge_for_ui_admin//managebookwindow_for_admin//preview.png");
    int data_row_num=data->get_row_num();
    for(int i=0;i<data_row_num;i++){
        QPushButton *changeBtn = new QPushButton();
        changeBtn->setMinimumSize(40,30);
        changeBtn->setMaximumSize(40,30);
        changeBtn->setIcon(changebtn_ico);
        changeBtn->setIconSize(QSize(28,28));
        QPushButton* delBtn = new QPushButton();
        delBtn->setMinimumSize(40,30);
        delBtn->setMaximumSize(33,33);
        delBtn->setIcon(delbtn_ico);
        delBtn->setIconSize(QSize(28,28));
        QPushButton* previewBtn = new QPushButton();
        previewBtn->setMinimumSize(40,30);
        previewBtn->setMaximumSize(33,33);
        previewBtn->setIcon(previewbtn_ico);
        previewBtn->setIconSize(QSize(28,28));
        table->setCellWidget(i,0,previewBtn);
        table->setCellWidget(i,1,changeBtn);
        table->setCellWidget(i,2,delBtn);
        //关联信号与槽
        QObject::connect(changeBtn,SIGNAL(clicked()),window,SLOT(change_book_info()));
        QObject::connect(delBtn,SIGNAL(clicked()),window,SLOT(removeRecord()));
        QObject::connect(previewBtn,SIGNAL(clicked()),window,SLOT(preview()));
        //保存指向new出来的QPushButton的指针，方便之后刷新页面时释放对应内存
        w->btn_vec.push_back(changeBtn);
        w->btn_vec.push_back(delBtn);
        w->btn_vec.push_back(previewBtn);
    }
}

display_for_managebookwindow_for_admin& display_for_managebookwindow_for_admin::instance(){
    static display_for_managebookwindow_for_admin d;
    return d;
}
