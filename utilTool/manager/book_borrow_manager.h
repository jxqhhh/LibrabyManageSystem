#ifndef BOOK_BORROW_MANAGER_H
#define BOOK_BORROW_MANAGER_H

#include <QString>
#include "utilTool/data_linear.h"
class book_borrow_manager
{
    book_borrow_manager()=delete;
    ~book_borrow_manager()=delete;
public:
    static int book_borrow(QString& book_id,QString& date_start,QString& date_end);
    static bool load_book_borrow_application_for_admin(data_linear* data,QStringList& param);
    static bool load_book_unreturned_for_admin(data_linear* data,QStringList& param);
    static int book_borrow_check(QString& book_id,QString& name_id,QString action);//审核图书借阅申请，根据action决定同意还是拒绝申请
    static int book_return(QString& book_id,QString& name_id);//将某本图书设置为已归还
    static bool load_book_borrow_current_state_for_user(data_linear* data);
    static bool load_book_borrow_history_for_user(data_linear* data);
};

#endif // BOOK_BORROW_MANAGER_H
