#include "auditwindow_for_admin.h"
#include"ui_auditwindow_for_admin.h"
#include "utilTool/data_linear.h"
#include "utilTool/manager/book_borrow_manager.h"
#include <QDebug>
#include <QMessageBox>
#include "utilTool/QStringLiteral.h"
AuditWindow_For_Admin::AuditWindow_For_Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuditWindow_For_Admin)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
    data_book_borrow_application=new data_linear();
    data_book_unreturned=new data_linear();
    ui->commandLinkButton_retrieve->click();
}

AuditWindow_For_Admin::~AuditWindow_For_Admin()
{
    delete ui;
    delete data_book_borrow_application;
    delete data_book_unreturned;
    for(int i=0;i<btn_vec_book_borrow_application_table.size();i++){
        delete btn_vec_book_borrow_application_table[i];
    }
    btn_vec_book_borrow_application_table.clear();
    for(int i=0;i<btn_vec_book_unreturned_table.size();i++){
        delete btn_vec_book_unreturned_table[i];
    }
    btn_vec_book_unreturned_table.clear();
}




void AuditWindow_For_Admin::on_comboBox_activated(int index)
{
    if(index==0){
        ui->lineEdit_book_name->setDisabled(true);
        ui->lineEdit_isbn->setDisabled(true);
    }else if(index==1){
        ui->lineEdit_book_name->setDisabled(false);
        ui->lineEdit_isbn->setDisabled(false);
    }
}

void AuditWindow_For_Admin::on_comboBox_2_activated(int index)
{
    if(index==0){
        ui->lineEdit_person_id->setDisabled(true);
        ui->lineEdit_person_name->setDisabled(true);
    }else if(index==1){
        ui->lineEdit_person_id->setDisabled(false);
        ui->lineEdit_person_name->setDisabled(false);
    }
}



void AuditWindow_For_Admin::on_commandLinkButton_retrieve_clicked()
{
    QStringList param;
    if(ui->comboBox->currentIndex()==0){
        param<<""<<"";
    }else{
        param<<ui->lineEdit_isbn->text()<<ui->lineEdit_book_name->text();
    }
    if(ui->comboBox_2->currentIndex()==0){
        param<<""<<"";
    }else{
        param<<ui->lineEdit_person_id->text()<<ui->lineEdit_person_name->text();
    }
    data_book_borrow_application->clear();
    book_borrow_manager::load_book_borrow_application_for_admin(data_book_borrow_application,param);
    book_borrow_manager::load_book_unreturned_for_admin(data_book_unreturned,param);
    display_for_auditwindow_bookborrow_for_admin::instance().display(data_book_borrow_application,ui->tableWidget_borrowing_audition,this);
    display_for_auditwindow_bookreturn_for_admin::instance().display(data_book_unreturned,ui->tableWidget_book_return,this);
}

void AuditWindow_For_Admin::accept_application(){
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
        QMessageBox::critical(NULL,"Error",QStringLiteral("未知错误，请重试！"),QMessageBox::Yes);
         return;
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget_borrowing_audition->indexAt(QPoint(x, y));
    int row = index.row();
    QString book_id=data_book_borrow_application->get_content(row,1);
    QString name_id=data_book_borrow_application->get_content(row,0);
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("提示"),
                                   QStringLiteral("确认同意借阅申请?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::No){
        return;
    }else if(button == QMessageBox::Yes){
        int result=book_borrow_manager::book_borrow_check(book_id,name_id,QString("accept"));
        switch(result){
            case 0:
                QMessageBox::critical(NULL,"Error",QStringLiteral("数据库操作错误，请重试！"),QMessageBox::Yes);
                break;
            case 1:
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("该图书无库存，无法同意申请！"));
                break;
            default:
                data_book_borrow_application->remove_row(row);                
                display_for_auditwindow_bookborrow_for_admin::instance().display(data_book_borrow_application,ui->tableWidget_borrowing_audition,this);
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("操作成功！"));
                break;
        }
    }
}

void AuditWindow_For_Admin::reject_application(){
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
         QMessageBox::critical(NULL,"Error",QStringLiteral("未知错误，请重试！"),QMessageBox::Yes);
         return;\
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget_borrowing_audition->indexAt(QPoint(x, y));
    int row = index.row();
    QString book_id=data_book_borrow_application->get_content(row,1);
    QString name_id=data_book_borrow_application->get_content(row,0);
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("提示"),
                                   QStringLiteral("确认拒绝借阅申请?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::No){
        return;
    }else if(button == QMessageBox::Yes){
        int result=book_borrow_manager::book_borrow_check(book_id,name_id,QString("reject"));
        switch(result){
            case 0:
                QMessageBox::critical(NULL,"Error",QStringLiteral("数据库操作错误，请重试！"),QMessageBox::Yes);
                break;
            default:
                data_book_borrow_application->remove_row(row);               
                display_for_auditwindow_bookborrow_for_admin::instance().display(data_book_borrow_application,ui->tableWidget_borrowing_audition,this);
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("操作成功！"));
                break;
        }
    }
}

void AuditWindow_For_Admin::return_book(){
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
         QMessageBox::critical(NULL,"Error",QStringLiteral("未知错误，请重试！"),QMessageBox::Yes);
         return;\
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget_book_return->indexAt(QPoint(x, y));
    int row = index.row();
    QString book_id=data_book_unreturned->get_content(row,1);
    QString name_id=data_book_unreturned->get_content(row,0);
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("提示"),
                                   QStringLiteral("确认将这本书设为已归还?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::No){
        return;
    }else if(button == QMessageBox::Yes){
        int result=book_borrow_manager::book_return(book_id,name_id);
        switch(result){
            case 0:
                QMessageBox::critical(NULL,"Error",QStringLiteral("数据库操作错误，请重试！"),QMessageBox::Yes);
                break;
            default:
                data_book_unreturned->remove_row(row);
                display_for_auditwindow_bookreturn_for_admin::instance().display(data_book_unreturned,ui->tableWidget_book_return,this);
                QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("操作成功！"));
                break;
        }
    }
}

void AuditWindow_For_Admin::load_all(){
    QStringList param;
        param<<""<<"";
        param<<""<<"";
    data_book_borrow_application->clear();
    data_book_unreturned->clear();
    book_borrow_manager::load_book_borrow_application_for_admin(data_book_borrow_application,param);
    book_borrow_manager::load_book_unreturned_for_admin(data_book_unreturned,param);
    display_for_auditwindow_bookborrow_for_admin::instance().display(data_book_borrow_application,ui->tableWidget_borrowing_audition,this);
    display_for_auditwindow_bookreturn_for_admin::instance().display(data_book_unreturned,ui->tableWidget_book_return,this);
}
