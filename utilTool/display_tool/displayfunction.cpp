#include "displayfunction.h"
#include "utilTool/data_linear.h"
#include <QString>
#include <QStringList>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include "utilTool/QStringLiteral.h"
#include <QPushButton>
#include <QHeaderView>
#include <QIcon>
#include <QSize>

void DisplayFunction::display_data_linear_without_btn(data_linear* data,QTableWidget* table,int btn_num,QStringList btn_name){
    int data_row_num=data->get_row_num();
    int data_column_num=data->get_column_num();
    int column_start=data->display_column_start;
    int column_end=data->display_column_end;
    //table初始化
    table->clear();
    table->setRowCount(data_row_num);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(column_end-column_start+1+btn_num);
    QStringList list=data->get_horizontal_labels();
    for(int i=0;i<btn_num;i++){
        list.insert(0,btn_name[btn_num-1-i]);
    }
    table->setHorizontalHeaderLabels(list);
    table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    for(int i=0;i<btn_num;i++){
        table->horizontalHeader()->setResizeMode(i,QHeaderView::ResizeToContents);
    }
    for(int i=0;i<data_row_num;i++){
        for(int j=0;j<column_end-column_start+1;j++){
            table->setItem(i,j+btn_num,new QTableWidgetItem(data->get_content(i,j+column_start)));
            table->item(i,j+btn_num)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void DisplayFunction::information(QString head, QString cause, QWidget* window){
    QMessageBox::information(window,head,cause,QMessageBox::Accepted);
}

int DisplayFunction::question(QString head, QString question, QWidget *window){
    return QMessageBox::question(window,head,question,QMessageBox::Accepted,QMessageBox::Rejected);
}

void DisplayFunction::normal(QTableWidget *table){
    //QAbstractItemView::setSelectionBehavior(QAbstractItemView::SingleSelection);
}

void DisplayFunction::display_information(QString content, QTableWidget *table){
    table->setRowCount(1); table->setColumnCount(1);
    table->setItem(0,0,new QTableWidgetItem(content));
}
