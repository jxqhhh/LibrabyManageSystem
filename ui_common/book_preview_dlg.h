#ifndef BOOK_PREVIEW_DLG_H
#define BOOK_PREVIEW_DLG_H

#include <QDialog>

namespace Ui {
class book_preview_dlg;
}

class book_preview_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit book_preview_dlg(QString book_id,QWidget *parent = 0);
    ~book_preview_dlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::book_preview_dlg *ui;
    QString book_id;
};

#endif // BOOK_PREVIEW_DLG_H
