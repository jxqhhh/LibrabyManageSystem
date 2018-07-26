#include "managebookwindow_for_user.h"
#include "ui_managebookwindow_for_user.h"
#include <QMessageBox>
#include <QModelIndex>
#include "ui_common/book_preview_dlg.h"
#include "set_loan_period_dialog.h"
#include "utilTool/manager/book_retrieve_manager.h"
ManageBookWindow_For_User::ManageBookWindow_For_User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageBookWindow_For_User)
{
    ui->setupUi(this);

}

ManageBookWindow_For_User::~ManageBookWindow_For_User()
{
    delete ui;
    for(int i=0;i<data_linear_vector.size();i++){
        delete data_linear_vector[i];
    }
    data_linear_vector.clear();
    for(int i=0;i<btn_vec.size();i++){
        delete btn_vec[i];
    }
    btn_vec.clear();
}

void ManageBookWindow_For_User::on_pushButton_re_retrieve_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("Warning"),
                                   QStringLiteral("重新检索会基于整个数据库重新检索，将会抛弃上一次的检索结果，确认继续?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No){
        ;  //忽略，程序继续运行
    }else if (button == QMessageBox::Yes) {
        for(int i=0;i<data_linear_vector.size();i++){
            delete data_linear_vector[i];
        }
        data_linear_vector.clear();
        data_linear* data_new=new data_linear();
        QStringList param;
        param<<ui->lineEdit_isbn->text()<<ui->lineEdit_name->text()<<ui->lineEdit_author->text()<<ui->lineEdit_publisher->text();
        if(ui->comboBox_is_available->currentIndex()==0){
            param<<"Unlimited";
        }else{
            param<<"Available";
        }
        if(!book_retrieve_manager::book_retrieve(data_new,param)){
            QMessageBox::critical(NULL,"Error",QStringLiteral("出现错误，请重试"),QMessageBox::Yes);
            return;
        };
        data_linear_vector.push_back(data_new);
        display_for_managebookwindow_for_user::instance().display(data_new,ui->tableWidget,this);

    }
}

void ManageBookWindow_For_User::load_all_book(){
    for(int i=0;i<btn_vec.size();i++){
        delete data_linear_vector[i];
    }
    data_linear_vector.clear();
    data_linear* data_new=new data_linear();
    QStringList param;
    param<<""<<""<<""<<""<<"Unlimited";
    if(!book_retrieve_manager::book_retrieve(data_new,param)){
        QMessageBox::critical(NULL,"Error",QStringLiteral("数据初始化出现错误！"),QMessageBox::Yes);
        return;
    };
    data_linear_vector.push_back(data_new);
    display_for_managebookwindow_for_user::instance().display(data_new,ui->tableWidget,this);
}

void ManageBookWindow_For_User::book_borrow(){

    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请重试"),QMessageBox::Yes);
         return;\
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    data_linear* data=data_linear_vector.operator [](data_linear_vector.size()-1);
    QString book_id=data->get_content(row,0);
    set_loan_period_dialog dlg(book_id);
    dlg.exec();
}

void ManageBookWindow_For_User::on_pushButton_further_retrieve_clicked()
{
    if(data_linear_vector.empty()){
        return;
    }
    data_linear* data_new=new data_linear();
    QStringList param;
    param<<ui->lineEdit_isbn->text()<<ui->lineEdit_name->text()<<ui->lineEdit_author->text()<<ui->lineEdit_publisher->text();
    if(ui->comboBox_is_available->currentIndex()==0){
        param<<"Unlimited";
    }else{
        param<<"Available";
    }
    if(!book_retrieve_manager::book_retrieve_from_current(data_new,data_linear_vector[data_linear_vector.size()-1],param)){
        QMessageBox::critical(NULL,"Error",QStringLiteral("出现错误，请重试"),QMessageBox::Yes);
        return;
    }
    data_linear_vector.push_back(data_new);
    display_for_managebookwindow_for_user::instance().display(data_new,ui->tableWidget,this);
}

void ManageBookWindow_For_User::on_pushButton_retrieve_by_sentence_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("Warning"),
                                   QStringLiteral("匹配检索会基于整个数据库重新检索，将会抛弃之前的检索结果，确认继续?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No){
        ;  //忽略，程序继续运行
    }else if (button == QMessageBox::Yes) {
        for(int i=0;i<data_linear_vector.size();i++){
            delete data_linear_vector[i];
        }
        data_linear_vector.clear();
        data_linear* data_new=new data_linear();
        QStringList param;
        param<<ui->textEdit_sentence->toPlainText();
        if(!book_retrieve_manager::book_retrieve(data_new,param)){
            QMessageBox::critical(NULL,"Error",QStringLiteral("出现错误，请重试"),QMessageBox::Yes);
            return;
        };
        data_linear_vector.push_back(data_new);
        display_for_managebookwindow_for_user::instance().display(data_new,ui->tableWidget,this);

    }
}

void ManageBookWindow_For_User::preview(){

    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请重试"),QMessageBox::Yes);
         return;\
    }
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    book_preview_dlg p_dlg(data_linear_vector[data_linear_vector.size()-1]->get_content(row,0));
    p_dlg.exec();
}

void ManageBookWindow_For_User::on_commandLinkButton_return_prev_retreive_result_clicked()
{
    if(data_linear_vector.size()>1){
        delete data_linear_vector[data_linear_vector.size()-1];
        data_linear_vector.pop_back();
        display_for_managebookwindow_for_user::instance().display(data_linear_vector[data_linear_vector.size()-1],ui->tableWidget,this);
    }
}
