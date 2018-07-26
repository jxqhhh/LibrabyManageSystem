#include "addbookdialog_for_admin.h"
#include "ui_addbookdialog_for_admin.h"
#include <QFileDialog>
#include "utilTool/QStringLiteral.h"
#include "utilTool/string_to_int_tool.h"
#include <QDebug>
AddBookDialog_For_Admin::AddBookDialog_For_Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog_For_Admin)
{
    ui->setupUi(this);
    ui->comboBox_is_date_unknown->setCurrentIndex(0);
    ui->dateEdit->setDisabled(true);
    ui->textEdit->document()->setMaximumBlockCount(1000);
}

AddBookDialog_For_Admin::~AddBookDialog_For_Admin()
{
    delete ui;
}

void AddBookDialog_For_Admin::on_comboBox_is_date_unknown_activated(int index)
{
    if(index==0){
        this->ui->dateEdit->setDisabled(true);
    }else if(index==1){
        this->ui->dateEdit->setDisabled(false);
    }
}

void AddBookDialog_For_Admin::on_commandLinkButton_clicked()
{
    QFileDialog::getOpenFileName(NULL,QStringLiteral("选择预览文件"),".","*.pdf");
}

void AddBookDialog_For_Admin::on_pushButton_ok_clicked()
{
    if(ui->lineEdit_name->text()==""){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请输入书名！"),QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_isbn->text()==""){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请输入ISBN！"),QMessageBox::Yes);
        return;
    }
    if((ui->lineEdit_num_total->text()=="")|(!string_to_int_tool::valid(ui->lineEdit_num_total->text().toStdString()))|(!(string_to_int_tool::string_to_int(ui->lineEdit_num_total->text().toStdString())>0))){
        QMessageBox::critical(NULL,"Error",QStringLiteral("请输入有效的馆藏数！"),QMessageBox::Yes);
        return;
    }
    QStringList param;
    param<<ui->lineEdit_book_type->text()<<ui->lineEdit_isbn->text()<<ui->lineEdit_name->text()<<
           ui->lineEdit_author->text()<<ui->lineEdit_publisher->text()<<ui->lineEdit_num_total->text();
    if(ui->comboBox_is_date_unknown->currentIndex()==0){
        param<<"Date_Unknown";
    }else{
        QString strYear = ui->dateEdit->sectionText(QDateTimeEdit::YearSection);
        QString strMonth = ui->dateEdit->sectionText(QDateTimeEdit::MonthSection);
        if(strMonth.length()==1){
            strMonth=QString("0")+strMonth;
        }
        QString strDay = ui->dateEdit->sectionText(QDateTimeEdit::DaySection);
        if(strDay.length()==1){
            strDay=QString("0")+strDay;
        }
        qDebug((strYear+QString("-")+strMonth+QString("-")+strDay).toStdString().c_str());
        param<<(strYear+QString("-")+strMonth+QString("-")+strDay);
    }
    param<<ui->textEdit->toPlainText();
    int state=book_retrieve_manager::add_book_record(param);
    if(state==-1){
        QMessageBox::critical(NULL,"Error",QStringLiteral("系统中已经存在ISBN相同的书籍，请勿重复添加！"),QMessageBox::Yes);
        return;
    }else if(state==0){
        QMessageBox::critical(NULL,"Error",QStringLiteral("数据库连接出现问题，请重试！"),QMessageBox::Yes);
        return;
    }else if(state==1){
        QMessageBox::about(nullptr,QStringLiteral("提示"),QStringLiteral("添加成功！"));
    }
}


