#ifndef BOOK_RETRIEVE_MANAGER_H
#define BOOK_RETRIEVE_MANAGER_H

#include "utilTool/data_linear.h"
#include <QStringList>
#include "utilTool/sqlfunction.h"
class book_retrieve_manager
{
    book_retrieve_manager()=delete;
    ~book_retrieve_manager()=delete;
public:
    static bool book_retrieve(data_linear* data,QStringList& param);//条件筛选检索
    static bool book_retrieve_from_current(data_linear* data_new, data_linear* data_current, QStringList& param);
    static bool latest_book_retrieve(data_linear* data);
    static bool book_record_delete_all(int id);
    static QString load_e_book(QString& book_id);
    static int add_book_record(QStringList& param);
    static bool load_book_info(data_linear* data,QString book_id);
    static int update_book_info(QString book_id,QString num_total,QString abstraction);
};

#endif // BOOK_RETRIEVE_MANAGER_H
