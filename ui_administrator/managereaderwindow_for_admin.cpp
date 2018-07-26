#include "managereaderwindow_for_admin.h"
#include "addreaderdialog_for_admin.h"
#include "utilTool/QStringLiteral.h"
#include <QMessageBox>
#include "ui_managereaderwindow_for_admin.h"
#include "utilTool/manager/reader_retrieve_manager.h"
ManageReaderWindow_For_Admin::ManageReaderWindow_For_Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageReaderWindow_For_Admin)
{
    ui->setupUi(this);
    data=new data_linear();

}

ManageReaderWindow_For_Admin::~ManageReaderWindow_For_Admin()
{
    delete ui;
    delete data;
    for(int i=0;i<btn_vec.size();i++){
        delete btn_vec[i];
    }
    btn_vec.clear();
}




void ManageReaderWindow_For_Admin::on_pushButton_retrieve_clicked()
{
    QStringList param;
    param<<ui->lineEdit->text()<<ui->lineEdit_2->text();
    data->clear();
    reader_retrieve_manager::reader_retrieve(data,param);
    display_for_managereaderwindow_for_admin::instance().display(data,ui->tableWidget,this);

}
void ManageReaderWindow_For_Admin::delete_reader(){
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请重试"),QMessageBox::Yes);
         return;\
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("Warning"),
                                   QStringLiteral("该操作将会从系统中永久删除关于该读者的记录，确认继续?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No){
        ;  //忽略，程序继续运行
    }else if (button == QMessageBox::Yes){
        int result=reader_retrieve_manager::delete_reader(data->get_content(row,0));
        switch(result){
            case 1:
                QMessageBox::critical(NULL,"Error",QStringLiteral("没有权限删除管理员，请重试！"),QMessageBox::Yes);
                break;
            case 2:
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("该用户尚有图书未归还，请归还后删除！"));
                break;
            case 3:
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("操作成功！"));
                data->remove_row(row);                
                display_for_managereaderwindow_for_admin::instance().display(data,ui->tableWidget,this);
                break;
        }
    }
}

void ManageReaderWindow_For_Admin::load_all(){
    QStringList param;
    param<<ui->lineEdit->text()<<ui->lineEdit_2->text();
    data->clear();
    reader_retrieve_manager::reader_retrieve(data,param);
    display_for_managereaderwindow_for_admin::instance().display(data,ui->tableWidget,this);

}
