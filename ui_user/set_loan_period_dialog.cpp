#include "set_loan_period_dialog.h"
#include "ui_set_loan_period_dialog.h"
#include <QDateTime>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include "utilTool/QStringLiteral.h"
#include "utilTool/manager/book_borrow_manager.h"
set_loan_period_dialog::set_loan_period_dialog(QString& book_id,QWidget *parent) :
    book_id(book_id),QDialog(parent),
    ui(new Ui::set_loan_period_dialog)
{
    ui->setupUi(this);

    QDateTime current_time=QDateTime::currentDateTime();
    std::string current_year=current_time.toString(Qt::ISODate).toStdString().substr(0,4);
    int c_year=std::stoi(current_year,nullptr,10);
    std::string current_month=current_time.toString(Qt::ISODate).toStdString().substr(5,2);
    int c_month=std::stoi(current_month,nullptr,10);
    std::string current_day=current_time.toString(Qt::ISODate).toStdString().substr(8,2);
    int c_day=std::stoi(current_day,nullptr,10);
    ui->dateEdit_start->setDateTime(QDateTime(QDate(c_year,c_month,c_day)));
    ui->dateEdit_end->setDateTime(QDateTime(QDate(c_year,c_month,c_day)));

}

set_loan_period_dialog::~set_loan_period_dialog()
{
    delete ui;
}

void set_loan_period_dialog::on_pushButton_cancel_clicked()
{
    this->close();
}

bool set_loan_period_dialog::less_than(int year1, int month1, int day1, int year2, int month2, int day2){
    //先比较年份
    if(year1>year2){return false;}
    if(year1<year2){return true;}
    //再比较月份
    if(month1>month2){return false;}
    if(month1<month2){return true;}
    //最后比较day
    if(day1<day2){return true;}
    return false;
}

void set_loan_period_dialog::on_pushButton_commit_clicked()
{
    QDateTime current_time=QDateTime::currentDateTime();
    std::string current_year=current_time.toString(Qt::ISODate).toStdString().substr(0,4);
    int c_year=std::stoi(current_year,nullptr,10);
    std::string current_month=current_time.toString(Qt::ISODate).toStdString().substr(5,2);
    int c_month=std::stoi(current_month,nullptr,10);
    std::string current_day=current_time.toString(Qt::ISODate).toStdString().substr(8,2);
    int c_day=std::stoi(current_day,nullptr,10);

    int start_year=stoi(ui->dateEdit_start->sectionText(QDateTimeEdit::YearSection).toStdString(),nullptr,10);
    int start_month=stoi(ui->dateEdit_start->sectionText(QDateTimeEdit::MonthSection).toStdString(),nullptr,10);
    int start_day=stoi(ui->dateEdit_start->sectionText(QDateTimeEdit::DaySection).toStdString(),nullptr,10);

    int end_year=stoi(ui->dateEdit_end->sectionText(QDateTimeEdit::YearSection).toStdString(),nullptr,10);
    int end_month=stoi(ui->dateEdit_end->sectionText(QDateTimeEdit::MonthSection).toStdString(),nullptr,10);
    int end_day=stoi(ui->dateEdit_end->sectionText(QDateTimeEdit::DaySection).toStdString(),nullptr,10);

    if(less_than(start_year,start_month,start_day,c_year,c_month,c_day)){
        QMessageBox::critical(NULL,"Error",QStringLiteral("申请借阅的开始日期不应早于当前时间，请重新选择开始日期！"),QMessageBox::Yes);
        return;
    }
    if(less_than(end_year,end_month,end_day,start_year,start_month,start_day)){
        QMessageBox::critical(NULL,"Error",QStringLiteral("申请借阅的结束日期不应早于开始日期，请重新选择！"),QMessageBox::Yes);
        return;
    }
    QString date_start,date_end;
    date_start=ui->dateEdit_start->sectionText(QDateTimeEdit::YearSection)+QString("-")+ui->dateEdit_start->sectionText(QDateTimeEdit::MonthSection)+
            QString("-")+ui->dateEdit_start->sectionText(QDateTimeEdit::DaySection);
    date_end=ui->dateEdit_end->sectionText(QDateTimeEdit::YearSection)+QString("-")+ui->dateEdit_end->sectionText(QDateTimeEdit::MonthSection)+
            QString("-")+ui->dateEdit_end->sectionText(QDateTimeEdit::DaySection);
    int result=book_borrow_manager::book_borrow(book_id,date_start,date_end);
    switch (result){
        case 0:
            QMessageBox::critical(NULL,QStringLiteral("提示"),QStringLiteral("数据库连接出现问题，请检查网络连接情况"),QMessageBox::Yes);
            break;
        case 1:
            QMessageBox::critical(NULL,QStringLiteral("提示"),QStringLiteral("您已经申请过借阅此书，请等待管理员审核"),QMessageBox::Yes);
            break;
        case 2:
            QMessageBox::critical(NULL,QStringLiteral("提示"),QStringLiteral("您已经借阅了此书并尚未归还，请勿重复操作"),QMessageBox::Yes);
            break;
        case 3:
            QMessageBox::critical(NULL,QStringLiteral("提示"),QStringLiteral("您已经借阅了此书并过期未还，请及时归还"),QMessageBox::Yes);
            break;
        case 5:
            QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("申请成功，请等待管理员审核！"));
            break;
        default:
            break;
    }

}
