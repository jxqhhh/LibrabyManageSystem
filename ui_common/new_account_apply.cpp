#include "new_account_apply.h"
#include "ui_new_account_apply.h"
#include "utilTool/sqlfunction.h"
#include "utilTool/display_tool/displayfunction.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QLineEdit>
new_account_apply::new_account_apply(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_account_apply)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password_repeat->setEchoMode(QLineEdit::Password);
    ui->lineEdit_validity->setText(QStringLiteral("未检查"));
}

new_account_apply::~new_account_apply()
{
    delete ui;
}

void new_account_apply::on_pushButton_exit_clicked()
{
    emit quit();
    this->close();
}

void new_account_apply::on_pushButton_register_clicked()
{
    QString name=ui->lineEdit_name->text();
    QString password=ui->lineEdit_password->text();
    if(ui->lineEdit_password->text()!=ui->lineEdit_password_repeat->text()){
        DisplayFunction::information(QStringLiteral("创建新账户失败"),QStringLiteral("两次输入的密码不一致"),this);
        return;
    }
    if(SqlFunction::person_name_valid(name)==false){
        DisplayFunction::information(QStringLiteral("创建新账户失败"),QStringLiteral("无效的用户名"),this);
        return;
    }
    if(SqlFunction::add_person(name,password,"user")==false){
        DisplayFunction::information(QStringLiteral("创建新账户失败"),QStringLiteral("创建新账户失败"),this);
        return;
    }
    else{
        DisplayFunction::information(QStringLiteral("创建新账户成功"),QStringLiteral("即将返回登录界面"),this);
        emit quit();
        this->close();
        return;
    }
}

void new_account_apply::on_pushButton_clicked()
{
    if(SqlFunction::person_name_valid(ui->lineEdit_name->text())==true) ui->lineEdit_validity->setText(QStringLiteral("账号合法"));
    else ui->lineEdit_validity->setText(QStringLiteral("账号已被注册"));
}

void new_account_apply::on_lineEdit_name_textChanged(const QString &arg1)
{
    ui->lineEdit_validity->setText(QStringLiteral("未检查"));
}
