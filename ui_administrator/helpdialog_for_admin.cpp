#include "helpdialog_for_admin.h"
#include "ui_helpdialog_for_admin.h"
HelpDialog_For_Admin::HelpDialog_For_Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog_For_Admin)
{
    ui->setupUi(this);
}

HelpDialog_For_Admin::~HelpDialog_For_Admin()
{
    delete ui;
}
