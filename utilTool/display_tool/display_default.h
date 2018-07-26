#ifndef DISPLAY_DEFAULT_H
#define DISPLAY_DEFAULT_H


#include "displayfunction.h"

class display_default:public DisplayFunction
{
    display_default(const  display_default&)=delete;
    void operator=(const  display_default&)=delete;
    display_default();
public:
    void display(data_linear* data,QTableWidget* table,QMainWindow *window);
    static display_default& instance();
};

#endif // DISPLAY_DEFAULT_H
