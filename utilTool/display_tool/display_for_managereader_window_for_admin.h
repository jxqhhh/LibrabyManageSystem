#ifndef DISPLAY_FOR_MANAGEREADER_WINDOW_FOR_ADMIN_H
#define DISPLAY_FOR_MANAGEREADER_WINDOW_FOR_ADMIN_H

#include "displayfunction.h"


class display_for_managereaderwindow_for_admin:public DisplayFunction
{
    display_for_managereaderwindow_for_admin(const display_for_managereaderwindow_for_admin&)=delete;
    void operator=(const display_for_managereaderwindow_for_admin&)=delete;
    display_for_managereaderwindow_for_admin();
public:
    void display(data_linear* data,QTableWidget* table,QMainWindow *window);
    static display_for_managereaderwindow_for_admin& instance();
};

#endif // DISPLAY_FOR_MANAGEREADER_WINDOW_FOR_ADMIN_H
