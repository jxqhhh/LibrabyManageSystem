#ifndef READER_RETRIEVE_MANAGER_H
#define READER_RETRIEVE_MANAGER_H

#include "utilTool/data_linear.h"
#include <QString>
class reader_retrieve_manager
{  
    reader_retrieve_manager()=delete;
    ~reader_retrieve_manager()=delete;
public:
    static bool reader_retrieve(data_linear* data,QStringList& param);//条件筛选检索读者
    static int delete_reader(QString reader_id);
};

#endif // READER_RETRIEVE_MANAGER_H
