#ifndef SET_LOAN_PERIOD_DIALOG_H
#define SET_LOAN_PERIOD_DIALOG_H

#include <QDialog>

namespace Ui {
class set_loan_period_dialog;
}

class set_loan_period_dialog : public QDialog
{
    Q_OBJECT
    QString book_id;
public:
    explicit set_loan_period_dialog(QString& book_id,QWidget *parent = 0);
    ~set_loan_period_dialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_commit_clicked();

private:
    Ui::set_loan_period_dialog *ui;
    bool less_than(int year1,int month1,int day1,int year2,int month2,int day2);
};

#endif // SET_LOAN_PERIOD_DIALOG_H
