#include "book_preview_dlg.h"
#include "ui_book_preview_dlg.h"
#include "utilTool/manager/book_retrieve_manager.h"
book_preview_dlg::book_preview_dlg(QString book_id,QWidget *parent) :
    QDialog(parent),book_id(book_id),
    ui(new Ui::book_preview_dlg)
{
    ui->setupUi(this);
    ui->textBrowser->setText(book_retrieve_manager::load_e_book(book_id));
}

book_preview_dlg::~book_preview_dlg()
{
    delete ui;
}

void book_preview_dlg::on_pushButton_clicked()
{
    ui->textBrowser->setText(std::move(book_retrieve_manager::load_e_book(book_id)));
}
