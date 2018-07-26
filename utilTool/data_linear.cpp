#include "data_linear.h"
#include <QString>
#include <QStringList>
#include <vector>
#include <QDebug>
#include "QStringLiteral.h"
data_linear::data_linear(){
    column_num=-1;  row_num=-1;  display_column_start=-1;  display_column_end=-1;  initialized=false;
}

data_linear::~data_linear(){
    this->clear();
}
bool data_linear::empty(){
    return rows->empty();
}
bool data_linear::initialize(int row_num,int column_num, int display_column_start, int display_column_end)
{
    this->row_num=row_num; this->column_num=column_num; this->display_column_start=display_column_start; this->display_column_end=display_column_end;
    rows=new std::vector<std::vector<QString>*>(row_num);
    //children=new std::vector<data_linear*>(row_num);
    int i;
    for(i=0;i<row_num;i++){
        rows->push_back(new std::vector<QString>(column_num));
        //children->push_back(nullptr);
    }
    if(display_column_end==-1) display_column_end=column_num-1;
    initialized=true;
    return true;
}

bool data_linear::initialize(int column_num, int display_column_start, int display_column_end)
{
    //qDebug()<<"data_linear initializing"<<endl;
    this->row_num=0; this->column_num=column_num; this->display_column_start=display_column_start; this->display_column_end=display_column_end;
    column_name=new std::vector<QString>(column_num);
    rows=new std::vector<std::vector<QString>*>;
    column_num=rows->size();
    if(display_column_end==-1) display_column_end=column_num-1;
    initialized=true;
    return true;
}

bool data_linear::clear(){
    //qDebug()<<"clearing data_linear"<<endl;
    if(initialized==true){
        int i;
        horizontal_labels.clear();
        //delete rows;
        if(rows!=nullptr){
            for(i=0;i<row_num;i++){
                delete (*rows)[i];
            }
            delete rows;
            //delete children;
        }
        column_num=-1;  row_num=-1;  display_column_start=-1;  display_column_end=-1;
    }
    initialized=false;
    return true;
}

bool data_linear::add_content(QString content,int row, int column){
    if(!((0 <= row && row < row_num)&&(0<= column && column < column_num))) return false;
    rows->at(row)->at(column)=content;
    return true;
}

bool data_linear::add_content(QString content,int column){
    if(!(0 <= column && column < column_num)) return false;
    rows->at(row_num-1)->at(column)=content;
    return true;
}

QString data_linear::get_content(int row, int column){
    if(!(row_valid(row)==true && column_valid(column)==true)) return "Invalid Data";
    return rows->at(row)->at(column);
}

bool data_linear::add_row(){
    rows->push_back(new std::vector<QString>(column_num));
    //children->push_back(nullptr);
    row_num=rows->size();
    return true;
}

bool data_linear::add_column(QString value){

}

int data_linear::get_row_num(){
    return row_num;
}

int data_linear::get_column_num(){
    return column_num;
}

bool data_linear::remove_row(int row){
    if(!(0 <= row && row < row_num)){return false;}
    rows->erase(rows->begin()+row);
    row_num--;
    return true;
}

bool data_linear::set_horizontal_labels(QStringList &horizontal_labels){
    this->horizontal_labels=horizontal_labels;
    return true;
}

bool data_linear::add_horizontal_label(QString label){
    this->horizontal_labels.append(label);
    return true;
}

QStringList data_linear::get_horizontal_labels(){
    return this->horizontal_labels;
}

bool data_linear::row_valid(int row){
    if(0 <= row && row < row_num ) return true;
    else return false;
}

bool data_linear::row_valid(int row_start, int row_end){
    if(row_start<-1 || row_end< -1 || row_start >= row_num || row_end >= row_num || row_start > row_end) return false;
    else return true;
}

bool data_linear::column_valid(int column){
    if(0 <= column && column < column_num ) return true;
    else return false;
}

bool data_linear::column_valid(int column_start, int column_end){
    if(column_start<-1 || column_end< -1 || column_start >= column_num || column_end >= column_num || column_start > column_end) return false;
    else return true;
}



void data_linear::print(){
    qDebug()<<QString("row_num = %1 column_num=%2").arg(row_num).arg(column_num)<<endl;
    int i,j;
    for(i=0;i<row_num;i++){
        for(j=0;j<column_num;j++){
            qDebug()<<rows->at(i)->at(j)<<"#";
        }
        qDebug()<<endl;
    }
    qDebug()<<endl;
}

