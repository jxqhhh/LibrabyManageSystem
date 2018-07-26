#ifndef MANAGEBOOKWINDOW_FOR_USER_H
#define MANAGEBOOKWINDOW_FOR_USER_H

#include <QMainWindow>
#include <vector>
#include "utilTool/data_linear.h"
#include <QPushButton>
#include "utilTool/display_tool/display_for_managebookwindow_for_user.h"
using std::vector;

namespace Ui {
class ManageBookWindow_For_User;
}

class ManageBookWindow_For_User : public QMainWindow
{
    Q_OBJECT
    vector<data_linear*> data_linear_vector;
    vector<QPushButton*> btn_vec;
public:
    explicit ManageBookWindow_For_User(QWidget *parent = 0);
    ~ManageBookWindow_For_User();
    friend class book_retrieve_manager;
    friend class display_for_managebookwindow_for_user;

private slots:
    void on_pushButton_re_retrieve_clicked();
    void load_all_book();
    void book_borrow();
    void on_pushButton_further_retrieve_clicked();
    void preview();
    void on_pushButton_retrieve_by_sentence_clicked();

    void on_commandLinkButton_return_prev_retreive_result_clicked();

private:
    Ui::ManageBookWindow_For_User *ui;
};

#endif // MANAGEBOOKWINDOW_FOR_USER_H
