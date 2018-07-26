#include "homepage_for_user.h"
#include "ui_homepage_for_user.h"
#include "utilTool/display_tool/display_default.h"
#include "utilTool/manager/book_retrieve_manager.h"
#include "set_loan_period_dialog.h"
#include "ui_common/book_preview_dlg.h"
#include <QMessageBox>
HomePage_For_User::HomePage_For_User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage_For_User)
{
    data=new data_linear();
    ui->setupUi(this);
}

HomePage_For_User::~HomePage_For_User()
{
    delete ui;
    delete data;
}

void HomePage_For_User::load_latest_book(){
    book_retrieve_manager::latest_book_retrieve(data);
    display_default::instance().display(data,ui->tableWidget,this);
}
