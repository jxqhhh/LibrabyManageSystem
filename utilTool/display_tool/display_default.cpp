#include "display_default.h"

display_default::display_default()
{

}

void display_default::display(data_linear *data, QTableWidget *table, QMainWindow *window){
    QStringList tmp;
    display_data_linear_without_btn(data,table,0,tmp);
}

display_default& display_default::instance(){
    static display_default d;
    return d;
}
