#ifndef MANAGEREADERWINDOW_FOR_ADMIN_H
#define MANAGEREADERWINDOW_FOR_ADMIN_H

#include <QMainWindow>
#include "utilTool/data_linear.h"
#include <QStringList>
#include <vector>

#include "utilTool/display_tool/display_for_managereader_window_for_admin.h"
#include <QPushButton>
using std::vector;
namespace Ui {
class ManageReaderWindow_For_Admin;
}

class ManageReaderWindow_For_Admin : public QMainWindow
{
    Q_OBJECT
    vector<QPushButton*> btn_vec;
public:
    explicit ManageReaderWindow_For_Admin(QWidget *parent = 0);
    ~ManageReaderWindow_For_Admin();
    friend class display_for_managereaderwindow_for_admin;
private slots:
    void load_all();
    void delete_reader();
    void on_pushButton_retrieve_clicked();

private:
    Ui::ManageReaderWindow_For_Admin *ui;
    data_linear* data;
};

#endif // MANAGEREADERWINDOW_FOR_ADMIN_H
