#include "changebookinfodlg_for_admin.h"
#include "ui_changebookinfodlg_for_admin.h"
#include "utilTool/data_linear.h"
#include "utilTool/manager/book_retrieve_manager.h"
#include <QMessageBox>
changebookinfodlg_for_admin::changebookinfodlg_for_admin(QString book_id,QWidget *parent) :
    QDialog(parent),book_id(book_id),
    ui(new Ui::changebookinfodlg_for_admin)
{
    ui->setupUi(this);
    data_linear* data=new data_linear();
    book_retrieve_manager::load_book_info(data,book_id);
    ui->lineEdit_name->setText(data->get_content(0,0));
    ui->lineEdit_name->setDisabled(true);
    ui->lineEdit_num_available->setText(data->get_content(0,1));
    ui->lineEdit_num_available->setDisabled(true);
    ui->lineEdit_num_total->setText(data->get_content(0,2));
    ui->textEdit->setText(data->get_content(0,3));
}

changebookinfodlg_for_admin::~changebookinfodlg_for_admin()
{
    delete ui;
}

void changebookinfodlg_for_admin::on_pushButton_ok_clicked()
{
    int result=book_retrieve_manager::update_book_info(book_id,ui->lineEdit_num_total->text(),ui->textEdit->toPlainText());
    switch(result){
        case 1:
            QMessageBox::critical(NULL,"Error",QStringLiteral("数据库操作错误，请重试！"),QMessageBox::Yes);
            break;
        case 2:
            QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("修改后的馆藏数不应低于已经借阅的图书数，请重试！"));
            break;
        case 3:
            QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("操作成功！"));
            break;
    }
}
