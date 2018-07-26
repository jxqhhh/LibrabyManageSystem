#include "book_borrow_manager.h"
#include "utilTool/sqlfunction.h"


int book_borrow_manager::book_borrow(QString &book_id,QString &date_start,QString &date_end){
    return SqlFunction::book_borrow(book_id,date_start,date_end);
}

bool book_borrow_manager::load_book_borrow_application_for_admin(data_linear *data,QStringList& param){
    return SqlFunction::load_book_borrow_application_for_admin(data,param);
}

bool book_borrow_manager::load_book_unreturned_for_admin(data_linear *data, QStringList &param){
    return SqlFunction::load_book_unreturned_for_admin(data,param);
}

int book_borrow_manager::book_borrow_check(QString &book_id, QString &name_id,QString action){
    return SqlFunction::book_borrow_check(book_id,name_id,action);
}

bool book_borrow_manager::load_book_borrow_current_state_for_user(data_linear *data){
    return SqlFunction::load_book_borrow_current_state_for_user(data);
}

bool book_borrow_manager::load_book_borrow_history_for_user(data_linear *data){
    return SqlFunction::load_book_borrow_history_for_user(data);
}

int book_borrow_manager::book_return(QString &book_id, QString &name_id){
    return SqlFunction::book_return(book_id,name_id);
}
