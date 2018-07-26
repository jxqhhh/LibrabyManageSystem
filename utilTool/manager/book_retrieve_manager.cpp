#include "book_retrieve_manager.h"
#include <QMessageBox>

bool book_retrieve_manager::book_retrieve(data_linear* data,QStringList& param){
    return SqlFunction::book_retrieve(data,param);
}

bool book_retrieve_manager::book_retrieve_from_current(data_linear* data_new, data_linear* data_current, QStringList& param){
    data_new->initialize(8,2,7);
    int row_num=data_current->get_row_num();
    QString isbn=param[0];
    QString name=param[1];
    QString author=param[2];
    QString publisher=param[3];
    QString available_request=param[4];
    QStringList labels;
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("作者");
    labels<<QStringLiteral("出版社");
    labels<<QStringLiteral("出版日期");
    labels<<QStringLiteral("在架数");
    labels<<QStringLiteral("馆藏数");
    data_new->set_horizontal_labels(labels);
    int data_new_row_num=0;
    if(available_request==QString("Available")){
        for(int i=0;i<row_num;i++){
            bool valid=true;
            if(isbn.size()!=0){

                if(isbn!=data_current->get_content(i,1)){valid=false;}
            }
            if(name.size()!=0){
                if(name!=data_current->get_content(i,2)){valid=false;}
            }
            if(author.size()!=0){
                if(author!=data_current->get_content(i,3)){valid=false;}

            }
            if(publisher.size()!=0){
                if(publisher!=data_current->get_content(i,4)){valid=false;}
            }
            if(data_current->get_content(i,6)==QString("0")){
                valid=false;
            }
            if(valid){
                data_new->add_row();
                for(int j=0;j<8;j++){
                    data_new->add_content(data_current->get_content(i,j),data_new_row_num,j);
                }
                data_new_row_num++;
            }
        }
    }else{
        for(int i=0;i<row_num;i++){
            bool valid=true;
            if(isbn.size()!=0){

                if(isbn!=data_current->get_content(i,1)){valid=false;}
            }
            if(name.size()!=0){
                if(name!=data_current->get_content(i,2)){valid=false;}
            }
            if(author.size()!=0){
                if(author!=data_current->get_content(i,3)){valid=false;}

            }
            if(publisher.size()!=0){
                if(publisher!=data_current->get_content(i,4)){valid=false;}
            }
            if(valid){
                data_new->add_row();
                for(int j=0;j<8;j++){
                    data_new->add_content(data_current->get_content(i,j),data_new_row_num,j);
                }
                data_new_row_num++;
            }
        }
    }

    return true;
}
bool book_retrieve_manager::book_record_delete_all(int id){
    return SqlFunction::book_record_delete_all(id);
}

int book_retrieve_manager::add_book_record(QStringList &param){
    return SqlFunction::add_book_record(param);
}

QString book_retrieve_manager::load_e_book(QString &book_id){
    return SqlFunction::load_e_book(book_id);
}

bool book_retrieve_manager::load_book_info(data_linear *data, QString book_id){
    return SqlFunction::load_book_info(data,book_id);
}

int book_retrieve_manager::update_book_info(QString book_id, QString num_total, QString abstraction){
    return SqlFunction::update_book_info(book_id,num_total,abstraction);
}

bool book_retrieve_manager::latest_book_retrieve(data_linear *data){
    return SqlFunction::latest_book_retrieve(data);
}
