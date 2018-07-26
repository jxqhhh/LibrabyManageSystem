#include "logger.h"
#include "ui_logger.h"
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "utilTool/display_tool/displayfunction.h"
#include "utilTool/QStringLiteral.h"
#include "ui_common/new_account_apply.h"
logger::logger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logger)
{
    ui->setupUi(this);
    initialize();
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

logger::~logger()
{
    delete ui;
}

void logger::on_pushButton_login_clicked()
{
    if(SqlFunction::login(ui->lineEdit_name->text(),ui->lineEdit_password->text())==true){

        if(!SqlFunction::get_person_type_from_id()){
            DisplayFunction::information(QStringLiteral("登录失败"),QStringLiteral("无法判断帐号类型"),this);
        };
        if(SqlFunction::person_type==QString("user")){
            emit log_valid_user(ui->lineEdit_name->text());
        }else if(SqlFunction::person_type==QString("person")){
            emit log_valid_admin(ui->lineEdit_name->text());
        }
        this->hide();
    }
    else DisplayFunction::information(QStringLiteral("登录失败"),QStringLiteral("无效的账户或密码"),this);
}

void logger::on_pushButton_register_clicked()
{
    new_account_apply p;
    p.exec();
}
void logger::reshow(){
    this->show();
}
void logger::enter(){
    void initialize();
    this->show();
}
void logger::on_pushButton_exit_clicked()
{
    this->close();
}
QString logger::get_name(){
    return ui->lineEdit_name->text();
}

void logger::on_pushButton_connect_clicked()
{
    if(SqlFunction::create_connection()==true){
        ui->lineEdit_connection_state->setText(QStringLiteral("已连接至服务器"));
        ui->pushButton_login->setDisabled(false);
        ui->pushButton_register->setDisabled(false);
    }else{
        ui->lineEdit_connection_state->setText(QStringLiteral("未连接至服务器"));
        ui->pushButton_login->setDisabled(true);
        ui->pushButton_register->setDisabled(true);
    }
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}
void logger::initialize(){
    this->ui->lineEdit_name->setText("");
    this->ui->lineEdit_password->setText("");
    this->ui->pushButton_connect->click();
    this->ui->lineEdit_name->setFocus();
    this->ui->pushButton_login->setDefault(true);
}

