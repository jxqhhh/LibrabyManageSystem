#include "display_for_managebookwindow_for_user.h"
#include "ui_user/managebookwindow_for_user.h"
#include <QPushButton>
#include "utilTool/QStringLiteral.h"
#include <QDir>
#include <QCoreApplication>
display_for_managebookwindow_for_user::display_for_managebookwindow_for_user()
{

}

void display_for_managebookwindow_for_user::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    ManageBookWindow_For_User* w=dynamic_cast<ManageBookWindow_For_User*>(window);
    if(w==nullptr){return;}
    //释放之前的new出来的QPushButton
    for(int i=0;i<w->btn_vec.size();i++){
        delete w->btn_vec[i];
    }
    w->btn_vec.clear();
    //在table中加载出数据但不加载按钮
    QStringList btn_name;
    btn_name<<QStringLiteral("预览");
    btn_name<<QStringLiteral("借阅");
    display_data_linear_without_btn(data,table,2,btn_name);
    //加载按钮
    QIcon previewbtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//image_for_ui_user//managebookwindow_for_user//preview.png");
    QIcon borrowbtn_ico("C://Users//jxq//Desktop//2018.6.11//client//image//image_for_ui_user//managebookwindow_for_user//book_borrow.png");
    int data_row_num=data->get_row_num();
    for(int i=0;i<data_row_num;i++){
        QPushButton *previewBtn = new QPushButton();
        previewBtn->setMinimumSize(40,30);
        previewBtn->setMaximumSize(40,30);
        previewBtn->setIcon(previewbtn_ico);
        previewBtn->setIconSize(QSize(28,28));
        QPushButton* borrowBtn = new QPushButton();
        borrowBtn->setMinimumSize(40,30);
        borrowBtn->setMaximumSize(40,30);
        borrowBtn->setIcon(borrowbtn_ico);
        borrowBtn->setIconSize(QSize(28,28));
        table->setCellWidget(i,0,previewBtn);
        table->setCellWidget(i,1,borrowBtn);
        //关联信号与槽
        QObject::connect(previewBtn,SIGNAL(clicked()),window,SLOT(preview()));
        QObject::connect(borrowBtn,SIGNAL(clicked()),window,SLOT(book_borrow()));
        //保存指向new出来的QPushButton的指针，方便之后刷新页面时释放对应内存
        w->btn_vec.push_back(previewBtn);
        w->btn_vec.push_back(borrowBtn);
    }
}

display_for_managebookwindow_for_user& display_for_managebookwindow_for_user::instance(){
    static display_for_managebookwindow_for_user d;
    return d;
}
