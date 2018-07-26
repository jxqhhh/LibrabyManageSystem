#ifndef CHANGEBOOKINFODLG_FOR_ADMIN_H
#define CHANGEBOOKINFODLG_FOR_ADMIN_H

#include <QDialog>

namespace Ui {
class changebookinfodlg_for_admin;
}

class changebookinfodlg_for_admin : public QDialog
{
    Q_OBJECT
    QString book_id;
public:
    explicit changebookinfodlg_for_admin(QString book_id,QWidget *parent = 0);
    ~changebookinfodlg_for_admin();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::changebookinfodlg_for_admin *ui;
};

#endif // CHANGEBOOKINFODLG_FOR_ADMIN_H
