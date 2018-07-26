#ifndef MANAGEBOOKWINDOW_FOR_ADMIN_H
#define MANAGEBOOKWINDOW_FOR_ADMIN_H

#include <QMainWindow>
#include "widget_for_admin.h"
#include "utilTool/data_linear.h"
#include "utilTool/manager/book_retrieve_manager.h"
#include "utilTool/display_tool/display_for_managebookwindow_for_admin.h"
#include <QPushButton>

using std::vector;

namespace Ui {
class ManageBookWindow_For_Admin;
}

class ManageBookWindow_For_Admin : public QMainWindow
{
    Q_OBJECT
    vector<data_linear*> data_linear_vector;
    vector<QPushButton*> btn_vec;
    data_linear* data_by_sentence_retrieve;
public:
    explicit ManageBookWindow_For_Admin(QWidget *parent = 0);
    ~ManageBookWindow_For_Admin();
    friend class book_retrieve_manager;
    friend class display_for_managebookwindow_for_admin;
private slots:
    void on_pushButton_3_clicked();



    void on_pushButton_re_retrieve_clicked();

    void on_pushButton_further_retrieve_clicked();

    void on_commandLinkButton_return_prev_retreive_result_clicked();

    void change_book_info();

    void removeRecord();

    void load_all_book();


    void on_pushButton_retrieve_by_sentence_clicked();
    void preview();
private:
    Ui::ManageBookWindow_For_Admin *ui;
};

#endif // MANAGEBOOKWINDOW_FOR_ADMIN_H
