#ifndef BORROWINGMANAGEMENT_FOR_USER_H
#define BORROWINGMANAGEMENT_FOR_USER_H

#include <QMainWindow>
#include "utilTool/data_linear.h"

namespace Ui {
class BorrowingManagement_For_User;
}

class BorrowingManagement_For_User : public QMainWindow
{
    Q_OBJECT

public:
    explicit BorrowingManagement_For_User(QWidget *parent = 0);
    ~BorrowingManagement_For_User();
private slots:
    void on_pushButton_renew1_clicked();
    void on_pushButton_renew2_clicked();
    void load();
private:
    Ui::BorrowingManagement_For_User *ui;
    void load_book_borrow_current_state_for_user();
    void load_book_borrow_history_for_user();
    data_linear* data_book_borrow_current_info;
    data_linear* data_book_borrow_history;
};

#endif // BORROWINGMANAGEMENT_FOR_USER_H
