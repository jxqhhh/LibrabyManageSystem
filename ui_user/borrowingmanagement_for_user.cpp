#include "borrowingmanagement_for_user.h"
#include "ui_borrowingmanagement_for_user.h"
#include "utilTool/manager/book_borrow_manager.h"
#include "utilTool/display_tool/display_default.h"
BorrowingManagement_For_User::BorrowingManagement_For_User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BorrowingManagement_For_User)
{
    data_book_borrow_current_info=new data_linear();
    data_book_borrow_history=new data_linear();
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

}

BorrowingManagement_For_User::~BorrowingManagement_For_User()
{
    delete ui;
    delete data_book_borrow_current_info;
    delete data_book_borrow_history;
}

void BorrowingManagement_For_User::load_book_borrow_current_state_for_user(){
    book_borrow_manager::load_book_borrow_current_state_for_user(data_book_borrow_current_info);
    display_default::instance().display(data_book_borrow_current_info,ui->tableWidget,this);
}

void BorrowingManagement_For_User::load_book_borrow_history_for_user(){
    book_borrow_manager::load_book_borrow_history_for_user(data_book_borrow_history);
    display_default::instance().display(data_book_borrow_history,ui->tableWidget_2,this);
}

void BorrowingManagement_For_User::on_pushButton_renew1_clicked()
{
    load_book_borrow_current_state_for_user();
}

void BorrowingManagement_For_User::on_pushButton_renew2_clicked()
{
    load_book_borrow_history_for_user();
}

void BorrowingManagement_For_User::load(){
    load_book_borrow_current_state_for_user();
    load_book_borrow_history_for_user();
}
