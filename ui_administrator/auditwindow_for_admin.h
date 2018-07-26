#ifndef AUDITWINDOW_FOR_ADMIN_H
#define AUDITWINDOW_FOR_ADMIN_H

#include <QMainWindow>
#include "utilTool/data_linear.h"
#include <vector>
#include <QPushButton>

#include "utilTool/display_tool/display_for_auditwindow_bookborrow_for_admin.h"
#include "utilTool/display_tool/display_for_auditwindow_bookreturn_for_admin.h"
using std::vector;
namespace Ui {
class AuditWindow_For_Admin;
}

class AuditWindow_For_Admin : public QMainWindow
{
    Q_OBJECT
    vector<QPushButton*> btn_vec_book_borrow_application_table;
    vector<QPushButton*> btn_vec_book_unreturned_table;

public:
    explicit AuditWindow_For_Admin(QWidget *parent = 0);
    ~AuditWindow_For_Admin();
    friend class display_for_auditwindow_bookborrow_for_admin;
    friend class display_for_auditwindow_bookreturn_for_admin;
private slots:

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);


    void on_commandLinkButton_retrieve_clicked();

    void accept_application();

    void reject_application();

    void return_book();

    void load_all();
private:
    Ui::AuditWindow_For_Admin *ui;
    data_linear* data_book_borrow_application;//存储图书借阅申请
    data_linear* data_book_unreturned;//存储未归还图书
};

#endif // AUDITWINDOW_FOR_ADMIN_H
