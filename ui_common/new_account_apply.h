#ifndef NEW_ACCOUNT_APPLY_H
#define NEW_ACCOUNT_APPLY_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class new_account_apply;
}

class new_account_apply : public QDialog
{
    Q_OBJECT

public:
    explicit new_account_apply(QWidget *parent = 0);
    ~new_account_apply();
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

private:
    Ui::new_account_apply *ui;

signals:
    void quit();
};

#endif // NEW_ACCOUNT_APPLY_H
