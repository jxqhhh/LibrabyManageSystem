#include "addreaderdialog_for_admin.h"
#include "ui_addreaderdialog_for_admin.h"
AddReaderDialog_For_Admin::AddReaderDialog_For_Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddReaderDialog_For_Admin)
{
    ui->setupUi(this);
}

AddReaderDialog_For_Admin::~AddReaderDialog_For_Admin()
{
    delete ui;
}
