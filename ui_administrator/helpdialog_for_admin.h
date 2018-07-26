#ifndef HELPDIALOG_FOR_ADMIN_H
#define HELPDIALOG_FOR_ADMIN_H

#include <QDialog>

namespace Ui {
class HelpDialog_For_Admin;
}

class HelpDialog_For_Admin : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog_For_Admin(QWidget *parent = 0);
    ~HelpDialog_For_Admin();

private:
    Ui::HelpDialog_For_Admin *ui;
};

#endif // HELPDIALOG_FOR_ADMIN_H
