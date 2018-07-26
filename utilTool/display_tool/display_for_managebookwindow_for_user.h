#ifndef DISPLAY_FOR_MANAGEBOOKWINDOW_FOR_USER_H
#define DISPLAY_FOR_MANAGEBOOKWINDOW_FOR_USER_H

#include "displayfunction.h"


class display_for_managebookwindow_for_user:public DisplayFunction
{
    display_for_managebookwindow_for_user(const display_for_managebookwindow_for_user&)=delete;
    void operator=(const display_for_managebookwindow_for_user&)=delete;
    display_for_managebookwindow_for_user();
public:
    void display(data_linear* data,QTableWidget* table,QMainWindow *window);
    static display_for_managebookwindow_for_user& instance();
};

#endif // DISPLAY_FOR_MANAGEBOOKWINDOW_FOR_USER_H
