#include "sqlfunction.h"
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QDebug>
#include "QStringLiteral.h"
#include "string_to_int_tool.h"
#include <string>
#include <cstdlib>
#include <QDebug>
#include <QLatin1String>
#include <cstdlib>
QString SqlFunction::person_type;

QString SqlFunction::name;
QString SqlFunction::id;
QSqlDatabase SqlFunction::db;
QSqlQuery* SqlFunction::query;
bool SqlFunction::set_name(QString name){
    SqlFunction::name=name;
    if(SqlFunction::get_person_id_from_name(name,SqlFunction::id)==false) return false;
    return true;
}

bool SqlFunction::get_folder_root(QString& folder_root_id, QString person_id){
    qDebug()<<QString("getting folder_root id of person %1").arg(person_id)<<endl;
    if((*query).exec("select id from person_folder_root where person_id="+person_id+";")==false) return false;
    (*query).first();
    folder_root_id=(*query).value(0).toString();
    qDebug()<<QString("folder_root_id got: %1").arg(folder_root_id)<<endl;
    return true;
}

bool SqlFunction::get_child_leaves(QString folder_id, data_linear& data_child, data_linear& data_leaves){
    //查询子收藏夹
    if(SqlFunction::get_child_folder(folder_id,data_child)==false) return false;
    //查询叶子节点
    if(SqlFunction::get_leaves(folder_id,data_leaves)==false) return false;
    //data_child.print();
    //data_leaves.print();
    return true;
}

bool SqlFunction::get_child_folder(QString folder_id, data_linear& data){
    //qDebug()<<QString("getting child folder of %1").arg(folder_id)<<endl;
    if((*query).exec("select name,child_num,leaves_num,id from folder where father_id="+folder_id+";")==false) return false;
    data.clear();
    data.initialize(4,0,2);
    if(SqlFunction::load_data_linear(data,*query,0,3)==false) return false;
    //qDebug()<<QString("folder got")<<endl;
    return true;
}

bool SqlFunction::get_leaves(QString folder_id, data_linear& data){
    //qDebug()<<QString("getting child leaves of %1").arg(folder_id)<<endl;
    data.clear();
    data.initialize(3,0,0);//书名，叶子节点的编号，书的编号

    //查询book
    if((*query).exec(QString("select a.name, b.id, a.id from book a,folder_leaves b where b.father_id=%1 and a.id=b.book_id;").arg(folder_id))==false) return false;
    if(SqlFunction::load_data_linear(data,*query,0,1)==false) return false;
    //查询book_cluster
    if((*query).exec(QString("select a.name, b.id, a.id from book_cluster a,folder_leaves b where b.father_id=%1 and a.id=b.book_id;").arg(folder_id))==false) return false;
    if(SqlFunction::load_data_linear(data,*query,0,1)==false) return false;
    //qDebug()<<QString("leaves got")<<endl;
    return true;
}

bool SqlFunction::folder_delete(QString folder_id){
    if(QSqlDatabase::database().transaction()==false) return false;
    SqlFunction::folder_delete_DFS(folder_id);
    (*query).exec(QString("update folder set child_num=child_num-1 where id in (select father_id from folder where id=%1);").arg(folder_id));
    (*query).finish();
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

void SqlFunction::folder_delete_DFS(QString folder_id){
    //if(QSqlDatabase::database().transaction()==false) return false;
    SqlFunction::folder_leaves_delete(folder_id);
    (*query).exec(QString("select id from folder where father_id=%1").arg(folder_id));
    while((*query).next()){
        SqlFunction::folder_delete_DFS((*query).value(0).toString());
    }
    SqlFunction::item_delete_1("folder","id",folder_id);
    (*query).finish();
    /*
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    */
}

bool SqlFunction::folder_leaves_delete(QString folder_id){
    if(QSqlDatabase::database().transaction()==false) return false;
    SqlFunction::item_delete_1("folder_leaves","father_id",folder_id);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

bool SqlFunction::folder_move(QString folder_id, QString father_id, QString new_father_id){
    if(QSqlDatabase::database().transaction()==false) return false;
    //if(SqlFunction::folder_higher(new_father_id,father_id)==false) return false;
    (*query).exec(QString("update folder set child_num=child_num-1 where id=%1").arg(father_id));
    (*query).exec(QString("update folder set father_id=%1 where id=%2;").arg(new_father_id).arg(folder_id));
    (*query).exec(QString("update folder set child_num=child_num+1 where id=%1").arg(new_father_id));
    (*query).finish();
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

bool SqlFunction::folder_higher(QString folder_id1, QString folder_id2){
    if(QSqlDatabase::database().transaction()==false) return false;
    while(true){
        (*query).exec(QString("select father_id from folder where id=%1").arg(folder_id2));
        (*query).first();
        folder_id2=(*query).value(0).toString();
        if(folder_id1==folder_id2) return true;
        (*query).exec(QString("select type from folder_idlist where id=%1").arg(folder_id2));
        (*query).first();
        if((*query).value(0).toString()=="person_root") return false;
    }
    (*query).finish();
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

bool SqlFunction::add_folder(QString name, QString root_folder_id){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString folder_id;
    get_new_id("folder",folder_id,"folder");
    item_add_6("folder",folder_id,root_folder_id,"1","1",add_quotation(name),"'valid'");
    item_update_1("folder","child_num","child_num+1","id",root_folder_id);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

bool SqlFunction::add_leaves(QString book_id, QString root_folder_id){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString folder_id;
    SqlFunction::get_new_id("folder",folder_id,"leaf");
    SqlFunction::item_add_3("folder_leaves",folder_id,root_folder_id,book_id);
    SqlFunction::item_update_1("folder","leaves_num","childe_num+1","id",root_folder_id);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}
bool SqlFunction::person_name_valid(QString name){
    if((*query).exec(QString("select count(*) from person where name=%1;").arg(add_quotation(name)))==false) return false;
    (*query).first();
    if((*query).value(0).toInt()>0) return false;
    return true;
}
bool SqlFunction::person_name_unique(QString name){
    (*query).exec("select count(*) from person where name='"+name+"';");
    (*query).first();
    if((*query).value(0).toInt()>1) return false;
    else return true;
}
bool SqlFunction::get_person_id_from_name(QString name, QString &id){
    if((*query).exec(QString("select id from person where name=%1").arg(add_quotation(name)))==false) return false;
    (*query).first();
    id=(*query).value(0).toString();
    return true;
}
bool SqlFunction::get_person_name_from_id(QString id, QString &name){
    if((*query).exec(QString("select name from person where id=%1").arg(id))==false) return false;
    (*query).first();
    name=(*query).value(0).toString();
    return true;
}

bool SqlFunction::get_person_type_from_id(){
    if(QSqlDatabase::database().transaction()==false) return false;
    (*query).exec(QString("select * from person_idlist where id = %1").arg(SqlFunction::id));
    (*query).first();
    SqlFunction::person_type=(*query).value(1).toString();
    return true;
}

bool SqlFunction::add_person(QString name, QString password, QString person_type){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString person_id, folder_root_id;
    SqlFunction::get_new_id("person",person_id,person_type);
    SqlFunction::item_add_3("person",person_id,add_quotation(name),add_quotation(password));
    SqlFunction::get_new_id("folder",folder_root_id,"person_root");
    SqlFunction::item_add_4("person_folder_root",folder_root_id,person_id,"0","0");
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}
bool SqlFunction::login(QString name, QString password){
    (*query).exec(QString("select count(*) from person where name=%1 and password=%2;").arg(add_quotation(name)).arg(add_quotation(password)));
    (*query).first();
    if((*query).value(0).toInt()==1) {
        SqlFunction::name=name;
        if(get_person_id_from_name(SqlFunction::name,SqlFunction::id)){
            return true;
        }else{
            return false;
        }
    }
    else return false;
}
bool SqlFunction::password_change(QString name, QString password){
    return (*query).exec("update person set password='"+password+"' where name='"+name+"';");
}

bool SqlFunction::get_name(QString& name){
    name=SqlFunction::name;
    return false;
}


bool SqlFunction::create_connection(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("211.159.215.251");
    db.setPort(63142);
    db.setUserName("root");
    db.setPassword("qwerty123456");
    db.setDatabaseName("library");
    if(db.open()==false){
        return false;
    }else{
        query=new QSqlQuery();
        return true;
    }

}

bool SqlFunction::book_retrieve(data_linear* data_new,QStringList& param){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString limit;
    if(param.length()==1){
        limit=" where abstraction like '%"+param[0]+"%'";
    }else{
        if(!(param[0]=="")){
            limit+="isbn = ";
            limit+=add_quotation(param[0]);
            limit+=" and ";
        }
        if(!(param[1]=="")){
            limit+="name = ";
            limit+=add_quotation(param[1]);
            limit+=" and ";
        }
        if(!(param[2]=="")){
            limit+="author = ";
            limit+=add_quotation(param[2]);
            limit+=" and ";
        }
        if(!(param[3]=="")){
            limit+="publisher = ";
            limit+=add_quotation(param[3]);
            limit+=" and ";
        }
        if(param[4]=="Unlimited"){
            limit+=" 1 > 0 and ";
        }else if(param[4]=="Available"){
            limit+=" num_available > 0 and ";
        }
        if(limit!=""){
            limit.resize(limit.size()-5);
            limit=QString("where ")+limit;
        }
    }

    (*query).exec(QString("select id,isbn,name,author,publisher,publication_date,num_available,num_total from book ")+limit+QString(";"));
    data_new->initialize(8,2,7);
    int row_num=0;
    //QMessageBox::critical(NULL,"Error",("出现错误，请重试"),QMessageBox::Yes);
    while((*query).next()){
        if(!data_new->add_row()){return false;}
        for(int j=0;j<8;j++){
            if(!data_new->add_content((*query).value(j).toString(),row_num,j)){data_new->clear();return false;}
        }
        row_num++;
    }
    QStringList labels;
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("作者");
    labels<<QStringLiteral("出版社");
    labels<<QStringLiteral("出版日期");
    labels<<QStringLiteral("在架数");
    labels<<QStringLiteral("馆藏数");
    data_new->set_horizontal_labels(labels); 
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data_new->clear();
        return false;
    }
    return true;
}

bool SqlFunction::book_record_delete_all(int id){

    query->exec(QString("delete from book_object where book_id = %1;").arg(id));
    query->exec(QString("delete from book_borrow where book_id = %1;").arg(id));
    query->exec(QString("delete from book where id=%1 ;").arg(id));
    query->exec(QString("delete from book_idlist where id = %1 ;").arg(id));
    return true;
    //TODO：删除借阅这些书的记录
}

int SqlFunction::add_book_record(QStringList &param){
    if(QSqlDatabase::database().transaction()==false) return 0;
    QString book_id;
    SqlFunction::get_new_id("book",book_id,"");//申请book_id
    (*query).exec(QString("select * from book where isbn = %1;").arg(add_quotation(param[1])));
    if((*query).first()){
        return -1;//ISBN重复，报错
    }
    (*query).exec(QString("insert into book_idlist values(%1,%2)").arg(book_id).arg(add_quotation(param[0])));
    (*query).exec(QString("insert into book(id,isbn,name,author,publisher,num_available,num_total,abstraction) values(%1,%2,%3,%4,%5,%6,%7,%8)").
                  arg(book_id).arg(add_quotation(param[1])).arg(add_quotation(param[2])).
            arg(add_quotation(param[3])).arg(add_quotation(param[4])).arg(param[5]).arg(param[5]).arg(add_quotation(param[7])));
    if(param[6]!="Date_Unknown"){
        (*query).exec(QString("update book set publication_date = %1 where id = %2;").arg(add_quotation(param[6])).arg(book_id));
    }
    QString book_object_id;
    SqlFunction::get_new_id_multilple(QString("%1").arg("book_object"),book_object_id,"",param[5]);
    std::string tmp=book_object_id.toStdString();
    char tmp_char[]="hehedaqisile";
    qDebug(book_id.toStdString().c_str());
    for(int i=0;i<param[5].toInt();i++){
        itoa(string_to_int_tool::string_to_int(tmp)+i,tmp_char,10);
        query->exec(QString("insert into book_object(id,state,book_id) values(%1,%2,%3)").arg(QString("%1").arg(tmp_char)).arg(add_quotation(QString("%1").arg("available"))).arg(book_id));
    }
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return 0;
    }
    return 1;
}

QString SqlFunction::load_e_book(QString &book_id){
    query->exec(QString("select abstraction from book where id = %1;").arg(book_id));
    query->first();
    QString tmp(query->value(0).toString());
    return tmp;
}

bool SqlFunction::load_book_info(data_linear *data, QString book_id){
    query->exec(QString("select name,num_available,num_total,abstraction from book where id = %1;").arg(book_id));
    data->initialize(4,0,3);
    query->first();
    data->add_row();
    for(int i=0;i<4;i++){
        data->add_content(query->value(i).toString(),0,i);
    }
}

int SqlFunction::update_book_info(QString book_id, QString num_total, QString abstraction){
    if(QSqlDatabase::database().transaction()==false) return 1;
    query->exec(QString("select num_available,num_total from book where id=%1;").arg(book_id));
    query->first();
    int available_now=string_to_int_tool::string_to_int(query->value(0).toString().toStdString());
    int total_now=string_to_int_tool::string_to_int(query->value(1).toString().toStdString());
    int total_new=string_to_int_tool::string_to_int(num_total.toStdString());
    if(total_new<=total_now){
        if(total_new<total_now-available_now){
            return 2;
        }
        std::string tmp=std::to_string(total_now-total_new);
        query->exec(QString("update book set num_total=%1  where id=%2;").arg(num_total).arg(book_id));
        query->exec(QString("update book set num_available=num_available-%1 where id=%2;").arg(tmp.c_str()).arg(book_id));
        query->exec(QString("update book set abstraction=%1 where id =%2").arg(add_quotation(abstraction)).arg(book_id));

        query->exec(QString("delete from book_object  WHERE book_object.id IN "
                            "(select t.id FROM (select id FROM book_object  where book_object.book_id= %1"
                            " and book_object.state='available' LIMIT %2)as t)"
                            "and book_object.id>-1;").arg(book_id).arg(tmp.c_str()));
        if(QSqlDatabase::database().commit()==false){
            QSqlDatabase::database().rollback();
            return 1;
        }
        return 3;
    }else{
        std::string tmp=std::to_string(total_new-total_now);
        query->exec(QString("update book set num_total=%1  where id=%2;").arg(num_total).arg(book_id));
        query->exec(QString("update book set num_available=num_available+%1 where id=%2;").arg(tmp.c_str()).arg(book_id));
        query->exec(QString("update book set abstraction=%1 where id =%2").arg(add_quotation(abstraction)).arg(book_id));
        QString num(std::to_string(total_new-total_now).c_str());
        QString book_object_id;
        SqlFunction::get_new_id_multilple(QString("%1").arg("book_object"),book_object_id,"",num);
        std::string b_o_i=book_object_id.toStdString();
        char tmp_char[]="hehedaqisile";
        for(int i=0;i<total_new-total_now;i++){
            itoa(string_to_int_tool::string_to_int(b_o_i)+i,tmp_char,10);
            query->exec(QString("insert into book_object(id,state,book_id) values(%1,%2,%3)").arg(QString("%1").arg(tmp_char)).arg(add_quotation(QString("%1").arg("available"))).arg(book_id));
        }

        if(QSqlDatabase::database().commit()==false){
            QSqlDatabase::database().rollback();
            return 1;
        }
        return 3;
    }


}

bool SqlFunction::latest_book_retrieve(data_linear *data_new){
    if(QSqlDatabase::database().transaction()==false) return false;
    query->exec(QString("select id,isbn,name,author,publisher,publication_date,num_available,num_total from book order by id desc;"));
    data_new->initialize(8,2,7);
    int row_num=0;
    //QMessageBox::critical(NULL,"Error",("出现错误，请重试"),QMessageBox::Yes);
    while((*query).next()){
        if(!data_new->add_row()){return false;}
        for(int j=0;j<8;j++){
            if(!data_new->add_content((*query).value(j).toString(),row_num,j)){data_new->clear();return false;}
        }
        row_num++;
        if(row_num>=10)break;
    }
    QStringList labels;
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("作者");
    labels<<QStringLiteral("出版社");
    labels<<QStringLiteral("出版日期");
    labels<<QStringLiteral("在架数");
    labels<<QStringLiteral("馆藏数");
    data_new->set_horizontal_labels(labels);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data_new->clear();
        return false;
    }
    return true;
}

int SqlFunction::book_borrow(QString book_id, QString time_borrow, QString time_return){
    if(QSqlDatabase::database().transaction()==false) return 0;
    QString thing_id;
    //先判断这本书是否已经申请了借阅并且尚未被审核或尚未被归还
    //这里规定即使某本书没库存也可以申请，但这样的申请管理员无法通过，在book_borrow_check函数里会检查
    query->exec(QString("select state from book_borrow where person_id = %1 and book_id = %2;").arg(SqlFunction::id).arg(book_id));
    while(query->next()){
        QString state=query->value(0).toString();
        if(state!="returned" & state!="cancelled" & state!="rejected"){
            if(state=="unaudited"){return 1;}//已经申请，未审核
            if(state=="accepted"){return 2;}//正在借阅，未归还
            if(state=="overdue"){return 3;}//过期未还
        }
    }
    SqlFunction::get_new_id("thing",thing_id,"book_borrow");//申请thing_id
    QString book_name,isbn;
    query->exec(QString("select name,isbn from book where id = %1;").arg(book_id));
    query->first();
    book_name=query->value(0).toString();
    isbn=query->value(1).toString();
    SqlFunction::item_add_9(QString("book_borrow"),thing_id,book_id,SqlFunction::id,add_quotation(time_borrow),add_quotation(time_return),add_quotation("unaudited"),add_quotation(SqlFunction::name),add_quotation(book_name),add_quotation(isbn));
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return 0;
    }
    return 5;
}



int SqlFunction::book_borrow_check(QString& book_id,QString& name_id, QString action){
    if(!(action=="accept"||action=="reject")) return 0;
    if(QSqlDatabase::database().transaction()==false) return 0;
    query->exec(QString("select num_available from book where id = %1").arg(book_id));
    query->first();
    int num=std::stoi(query->value(0).toString().toStdString());
    if(num==0){
        return 1;
    }
    if(action=="accept"){
        query->exec(QString("update book_borrow set state = 'accepted' where book_id = %1 and person_id = %2 and state = 'unaudited' ;").arg(book_id).arg(name_id));
        query->exec(QString("update book set num_available=num_available-1 where id = %1;").arg(book_id));
        query->exec(QString("update book_object set book_object.person_id = %1 WHERE book_object.id IN "
                            "(select t.id FROM (select id FROM book_object  where book_object.book_id=%2 and book_object.state='available' LIMIT 1)as t) "
                            "and book_object.id>-1;").arg(name_id).arg(book_id));
        query->exec(QString("update book_object set book_object.state='accepted' WHERE book_object.id IN "
                            "(select t.id FROM (select id FROM book_object  where book_object.person_id=%1 and book_object.book_id=%2 LIMIT 1)as t) "
                            "and book_object.id>-1;").arg(name_id).arg(book_id));
    }else if(action=="reject"){
        query->exec(QString("update book_borrow set state = 'rejected' where book_id = %1 and person_id = %2 and state = 'unaudited' ;").arg(book_id).arg(name_id));
    }
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return 0;
    }
    return 2;
}

bool SqlFunction::load_book_borrow_application_for_admin(data_linear *data,QStringList& param){
    data->initialize(9,2,8);
    if(QSqlDatabase::database().transaction()==false) return false;
    QString limit("");
    if(param[0]!="" ){
        limit+=QString(" isbn = %1 and ").arg(add_quotation(param[0]));
    }
    if(param[1]!=""){
        limit+=QString(" book_name = %1 and ").arg(add_quotation(param[1]));
    }
    if(param[2]!=""){
        limit+=QString(" person_id = %1 and ").arg(param[2]);
    }
    if(param[3]!=""){
        limit+=QString(" person_name = %1 and ").arg(add_quotation(param[3]));
    }
    if(limit!=""){
        limit=QString("where ")+limit+QString(" state='unaudited' ");
    }else{
        limit=QString(" where state = 'unaudited' ");
    }
    qDebug(limit.toStdString().c_str());
    QSqlQuery query2;
    query->exec(QString("select person_id,book_id,person_name,book_name,isbn,date_borrow,date_return from book_borrow ")+limit+QString(";"));
    int row_num=0;
    while(query->next()){
        data->add_row();
        data->add_content(query->value(0).toString(),row_num,0);
        data->add_content(query->value(1).toString(),row_num,1);
        data->add_content(query->value(2).toString(),row_num,2);
        data->add_content(query->value(3).toString(),row_num,3);
        data->add_content(query->value(4).toString(),row_num,4);
        data->add_content(query->value(5).toString(),row_num,7);
        data->add_content(query->value(6).toString(),row_num,8);
        query2.exec(QString("select num_available,num_total from book where id = %1;").arg(query->value(1).toString()));
        query2.first();
        data->add_content(query2.value(0).toString(),row_num,5);
        data->add_content(query2.value(1).toString(),row_num,6);
        row_num++;
    }
    QStringList labels;
    labels<<QStringLiteral("申请人");
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("ISBN");
    labels<<QStringLiteral("库存数");
    labels<<QStringLiteral("馆藏数");
    labels<<QStringLiteral("借阅起始日期");
    labels<<QStringLiteral("借阅结束日期");
    data->set_horizontal_labels(labels);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data->clear();
        return false;
    }
    return true;
}

bool SqlFunction::load_book_unreturned_for_admin(data_linear *data, QStringList &param){
    data->initialize(8,2,7);
    if(QSqlDatabase::database().transaction()==false) return false;
    QString limit("");
    if(param[0]!="" ){
        limit+=QString(" isbn = %1 and ").arg(add_quotation(param[0]));
    }
    if(param[1]!=""){
        limit+=QString(" book_name = %1 and ").arg(add_quotation(param[1]));
    }
    if(param[2]!=""){
        limit+=QString(" person_id = %1 and ").arg(param[2]);
    }
    if(param[3]!=""){
        limit+=QString(" person_name = %1 and ").arg(add_quotation(param[3]));
    }
    if(limit!=""){
        limit=QString("where ")+limit+QString(" (state = 'accepted' or state = 'overdue') ");
    }else{
        limit=QString(" where state = 'accepted' or state = 'overdue'");
    }
    query->exec(QString("select person_id,book_id,person_name,book_name,isbn,date_borrow,date_return,state from book_borrow ")+limit+QString(";"));
    int row_num=0;
    while(query->next()){
        data->add_row();
        data->add_content(query->value(0).toString(),row_num,0);
        data->add_content(query->value(1).toString(),row_num,1);
        data->add_content(query->value(2).toString(),row_num,2);
        data->add_content(query->value(3).toString(),row_num,3);
        data->add_content(query->value(4).toString(),row_num,4);
        data->add_content(query->value(5).toString(),row_num,5);
        data->add_content(query->value(6).toString(),row_num,6);
        if(query->value(7).toString()=="accepted"){
            data->add_content(QStringLiteral("借阅中"),row_num,7);
        }else if(query->value(7).toString()=="overdue"){
            data->add_content(QStringLiteral("过期未还"),row_num,7);
        }
        row_num++;
    }
    QStringList labels;
    labels<<QStringLiteral("申请人");
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("ISBN");
    labels<<QStringLiteral("借阅起始日期");
    labels<<QStringLiteral("借阅结束日期");
    labels<<QStringLiteral("状态");
    data->set_horizontal_labels(labels);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data->clear();
        return false;
    }
    return true;
}

int SqlFunction::book_return(QString book_id, QString name_id){
    if(QSqlDatabase::database().transaction()==false) return 0;
    query->exec(QString("update book_borrow set state = 'returned' where book_id = %1 and person_id = %2 and (state='accepted' or state = 'overdue') ;").arg(book_id).arg(name_id));
    query->exec(QString("update book set num_available=num_available+1 where id = %1;").arg(book_id));
    query->exec(QString("update book_object set state='available' where book_id = %1 and person_id = %2 and (state='accepted' or state = 'overdue');").arg(book_id).arg(name_id));
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return 0;
    }
    return 1;
}

bool SqlFunction::load_book_borrow_current_state_for_user(data_linear *data){
    data->initialize(7,2,6);
    if(QSqlDatabase::database().transaction()==false) return false;
    query->exec(QString("select id,book_id,book_name,isbn,date_borrow,date_return,state from book_borrow where state = 'overdue' and person_id = %1 order by id;").arg(SqlFunction::id));
    int row_num=0;
    while(query->next()){
        data->add_row();
        data->add_content(query->value(0).toString(),row_num,0);
        data->add_content(query->value(1).toString(),row_num,1);
        data->add_content(query->value(2).toString(),row_num,2);
        data->add_content(query->value(3).toString(),row_num,3);
        data->add_content(query->value(4).toString(),row_num,4);
        data->add_content(query->value(5).toString(),row_num,5);
        data->add_content(QStringLiteral("过期未还"),row_num,6);
        row_num++;
    }
    query->exec(QString("select id,book_id,book_name,isbn,date_borrow,date_return,state from book_borrow where state = 'accepted' and person_id = %1 order by id;").arg(SqlFunction::id));
    while(query->next()){
        data->add_row();
        data->add_content(query->value(0).toString(),row_num,0);
        data->add_content(query->value(1).toString(),row_num,1);
        data->add_content(query->value(2).toString(),row_num,2);
        data->add_content(query->value(3).toString(),row_num,3);
        data->add_content(query->value(4).toString(),row_num,4);
        data->add_content(query->value(5).toString(),row_num,5);
        data->add_content(QStringLiteral("借阅中"),row_num,6);
        row_num++;
    }
    QStringList labels;
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("ISBN");
    labels<<QStringLiteral("借阅起始日期");
    labels<<QStringLiteral("借阅结束日期");
    labels<<QStringLiteral("状态");
    data->set_horizontal_labels(labels);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data->clear();
        return false;
    }
    return true;
}

bool SqlFunction::load_book_borrow_history_for_user(data_linear *data){
    data->initialize(7,2,6);
    if(QSqlDatabase::database().transaction()==false) return false;
    query->exec(QString("select id,book_id,book_name,isbn,date_borrow,date_return,state from book_borrow where person_id = %1 order by id;").arg(SqlFunction::id));
    int row_num=0;
    while(query->next()){
        data->add_row();
        data->add_content(query->value(0).toString(),row_num,0);
        data->add_content(query->value(1).toString(),row_num,1);
        data->add_content(query->value(2).toString(),row_num,2);
        data->add_content(query->value(3).toString(),row_num,3);
        data->add_content(query->value(4).toString(),row_num,4);
        data->add_content(query->value(5).toString(),row_num,5);
        if(query->value(6).toString()=="overdue"){
            data->add_content(QStringLiteral("过期未还"),row_num,6);
        }else if(query->value(6).toString()=="returned"){
            data->add_content(QStringLiteral("已归还"),row_num,6);
        }else if(query->value(6).toString()=="unaudited"){
            data->add_content(QStringLiteral("未审核"),row_num,6);
        }else if(query->value(6).toString()=="accepted"){
            data->add_content(QStringLiteral("借阅中"),row_num,6);
        }else if(query->value(6).toString()=="rejected"){
            data->add_content(QStringLiteral("申请失败"),row_num,6);
        }else{
            data->add_content("error",row_num,6);
        }
        row_num++;
    }
    QStringList labels;
    labels<<QStringLiteral("书名");
    labels<<QStringLiteral("ISBN");
    labels<<QStringLiteral("借阅起始日期");
    labels<<QStringLiteral("借阅结束日期");
    labels<<QStringLiteral("状态");
    data->set_horizontal_labels(labels);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data->clear();
        return false;
    }
    return true;
}

bool SqlFunction::reader_retrieve(data_linear *data, QStringList &param){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString limit;
    QSqlQuery query2;
    if(!(param[0]=="")){
        limit+=" id = ";
        limit+=param[0];
        limit+=" and ";
    }
    if(!(param[1]=="")){
        limit+=" name = ";
        limit+=add_quotation(param[1]);
        limit+=" and ";
    }
    limit+=" id>-1 and ";
    if(limit!=""){
        limit.resize(limit.size()-5);
        limit=QString("where ")+limit;
    }
    query->exec(QString("select id,name from person ")+limit+";");
    data->initialize(3,0,2);
    int row_num=0;
    while((*query).next()){
        data->add_row();
        for(int j=0;j<2;j++){
            data->add_content((*query).value(j).toString(),row_num,j);
        }
        query2.exec(QString("select person_type from person_idlist where id = %1").arg(query->value(0).toString().toStdString().c_str()));
        query2.first();
        if(query2.value(0).toString()=="person"){
            data->add_content(QStringLiteral("管理员"),row_num,2);
        }else{
            data->add_content(QStringLiteral("普通用户"),row_num,2);
        }
        row_num++;
    }
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        data->clear();
        return false;
    }
    QStringList labels;
    labels<<QStringLiteral("用户ID");
    labels<<QStringLiteral("用户名");
    labels<<QStringLiteral("用户类型");
    data->set_horizontal_labels(labels);
    return true;
}

int SqlFunction::delete_reader(QString& reader_id){
    //管理员没有权限删除管理员，如果发生这种情况会返回1
    query->exec(QString("select * from person_idlist where id = %1;").arg(reader_id));
    query->first();
    if(query->value(1).toString()=="person"){return 1;}
    //如果读者仍有图书未归还，也无法删除用户，会返回2
    query->exec(QString("select * from book_borrow where person_id=%1 and (state='accepted' or state='overdue')").arg(reader_id));
    if(query->next()){
        return 2;
    }
    item_delete_1("book_borrow","person_id",reader_id);
    item_delete_1("person","id",reader_id);
    item_delete_1("message","receiver_id",reader_id);
    item_delete_1("message","sender_id",reader_id);
    QString folder_root_id;
    get_folder_root(folder_root_id,reader_id);
    folder_delete(folder_root_id);
    item_delete_1("person_folder_root","person_id",reader_id);
    item_delete_1("comment","person_id",reader_id);
    item_delete_1("person_idlist","id",reader_id);
    return 3;

}

void SqlFunction::get_new_id(QString table_name,QString& new_id,QString type_name){
    (*query).exec(QString("select id_type_name from type_id_type where type_name=%1;)").arg(add_quotation(table_name)));
    (*query).first();
    QString id_type=(*query).value(0).toString();
    (*query).exec(QString("update idlist_%1 set id=id+1 where type=%2;").arg(id_type).arg(add_quotation(table_name)));
    (*query).exec(QString("select id from idlist_%1 where type=%2;").arg(id_type).arg(add_quotation(table_name)));
    (*query).first();
    new_id=(*query).value(0).toString();
    (*query).exec(QString("insert into %1_idlist values(%2,%3);").arg(table_name).arg(new_id).arg(add_quotation(type_name)));
}
void SqlFunction::get_new_id_multilple(QString table_name, QString &new_id, QString type_name, QString& count){
    query->exec(QString("select id_type_name from type_id_type where type_name=%1;)").arg(add_quotation(table_name)));
    query->first();
    QString id_type=(*query).value(0).toString();
    (*query).exec(QString("select id from idlist_%1 where type=%2;").arg(id_type).arg(add_quotation(table_name)));
    (*query).first();
    char tmp[]="hehedaqisile";
    itoa((*query).value(0).toInt()+1,tmp,10);
    new_id=QString("%1").arg(tmp);
    itoa(count.toInt(),tmp,10);
    qDebug("checkpoint 4");
    query->exec(QString("update idlist_%1 set id = id+%2 where type=%3;").arg(id_type).arg(QString("%1").arg(tmp)).arg(add_quotation(table_name)));
    qDebug("checkpoint 5");
}

bool SqlFunction::get_system_time(QString &now){
    if((*query).exec("update system time set time=sysdate();")==false) return false;
    if((*query).exec("select system_time from system_time where id=0;")==false) return false;
    (*query).first();
    now=(*query).value(0).toString();
    return true;
}
bool SqlFunction::add_thing(QString verb, QString thing_type){
    if(QSqlDatabase::database().transaction()==false) return false;
    QString thing_id,now;
    SqlFunction::get_system_time(now);
    SqlFunction::get_new_id("thing",thing_id,thing_type);
    SqlFunction::item_add_3("thing",add_quotation(verb),now,thing_id);
    if(QSqlDatabase::database().commit()==false){
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;
}

bool SqlFunction::load_data_linear(data_linear& data, QSqlQuery& query, int column_start=0, int column_end=-1){
    int i, j;
    if(column_end==-1) column_end=data.get_column_num()-1;
    if(data.column_valid(column_start,column_end)==false) return false;
    while((query).next()){
        data.add_row();
        i=0;
        for(j=column_start;j<=column_end;j++){
            data.add_content((query).value(i).toString(),j);
            i++;
        }
    }
    return true;
}

bool SqlFunction::write_data_linear(data_linear &data, QSqlQuery *query, int row_start, int row_end, int column_start, int column_end){
    int i,j;
    if(data.row_valid(row_start,row_end)==true && data.column_valid(column_start,column_end)==true && (*query).size()>=(row_end-row_start+1)){
        while((*query).next()){
            for(i=row_start;i<=row_end;i++){
                for(j=column_start;j<=column_end;j++){
                        data.add_content((*query).value(j).toString(),i,j);
                }
            }
        }
        return true;
    }
    else return false;
}

void SqlFunction::item_delete_1(QString table_name, QString prop1, QString val1){
    (*query).exec(QString("delete from %1 where %2 =%3;").arg(table_name).arg(prop1).arg(val1));
}

void SqlFunction::item_add_1(QString table_name, QString arg1){
    (*query).exec(QString("insert into %1 values(%2);").arg(table_name).arg(arg1));
}

void SqlFunction::item_add_2(QString table_name, QString arg1, QString arg2){
    (*query).exec(QString("insert into %1 values(%2,%3);").arg(table_name).arg(arg1).arg(arg2));
}

void SqlFunction::item_add_3(QString table_name, QString arg1, QString arg2, QString arg3){
    (*query).exec(QString("insert into %1 values(%2,%3,%4);").arg(table_name).arg(arg1).arg(arg2).arg(arg3));
}

void SqlFunction::item_add_4(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4){
    (*query).exec(QString("insert into %1 values(%2,%3,%4,%5);").arg(table_name).arg(arg1).arg(arg2).arg(arg3).arg(arg4));
}

void SqlFunction::item_add_5(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5){
     (*query).exec(QString("insert into %1 values(%2,%3,%4,%5,%6);").arg(table_name).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5));
}

void SqlFunction::item_add_6(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6){
     (*query).exec(QString("insert into %1 values(%2,%3,%4,%5,%6,%7);").arg(table_name).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6));
}

void SqlFunction::item_add_9(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6,QString arg7,QString arg8,QString arg9){
     (*query).exec(QString("insert into %1 values(%2,%3,%4,%5,%6,%7,%8,%9,%10);").arg(table_name).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6).arg(arg7).arg(arg8).arg(arg9));
}

void SqlFunction::item_update_1(QString table_name, QString prop, QString new_data, QString prop1, QString val1){
    (*query).exec(QString("update %1 set %2 = %3 where %4 = %5;").arg(table_name).arg(prop).arg(new_data).arg(prop1).arg(val1));
}

void SqlFunction::item_update_2(QString table_name, QString prop, QString new_data, QString prop1, QString val1, QString prop2, QString val2){
    (*query).exec(QString("update %1 set %2 = %3 where %4 = %5 and %6 = %7;").arg(table_name).arg(prop).arg(new_data).arg(prop1).arg(val1).arg(prop2).arg(val2));
}

QString SqlFunction::add_quotation(QString content){
    return "'"+content+"'";
}

bool SqlFunction::type_check(QString table_name, QString id, QString type_name){
    if((*query).exec(QString("select count(*) from %1_idlist where id=%2 and type=%3;").arg(table_name).arg(id).arg(add_quotation(type_name)))==false) return false;
    (*query).first();
    if((*query).value(0).toInt()!=1) return false;
}


