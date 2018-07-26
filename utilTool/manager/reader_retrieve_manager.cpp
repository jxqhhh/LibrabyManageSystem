#include "reader_retrieve_manager.h"
#include "utilTool/sqlfunction.h"
bool reader_retrieve_manager::reader_retrieve(data_linear *data, QStringList &param){
    return SqlFunction::reader_retrieve(data,param);
}

int reader_retrieve_manager::delete_reader(QString reader_id){
    return SqlFunction::delete_reader(reader_id);
}

