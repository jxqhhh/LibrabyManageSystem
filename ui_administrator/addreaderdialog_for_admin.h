#ifndef ADDREADERDIALOG_FOR_ADMIN_H
#define ADDREADERDIALOG_FOR_ADMIN__H

#include <QDialog>

namespace Ui {
class AddReaderDialog_For_Admin;
}

class AddReaderDialog_For_Admin : public QDialog
{
    Q_OBJECT

public:
    explicit AddReaderDialog_For_Admin(QWidget *parent = 0);
    ~AddReaderDialog_For_Admin();

private:
    Ui::AddReaderDialog_For_Admin *ui;
};

#endif // ADDREADERDIALOG__FOR_ADMIN_H
