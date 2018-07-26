#ifndef ADDBOOKDIALOG_FOR_ADMIN_H
#define ADDBOOKDIALOG_FOR_ADMIN_H

#include <QDialog>
#include "utilTool/manager/book_retrieve_manager.h"
#include <cstdlib>
#include <QMessageBox>
namespace Ui {
class AddBookDialog_For_Admin;
}

class AddBookDialog_For_Admin : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog_For_Admin(QWidget *parent = 0);
    ~AddBookDialog_For_Admin();

private slots:

    void on_commandLinkButton_clicked();

    void on_pushButton_ok_clicked();

    void on_comboBox_is_date_unknown_activated(int index);

private:
    Ui::AddBookDialog_For_Admin *ui;
};

#endif // ADDBOOKDIALOG_FOR_ADMIN_H
