#ifndef SQLFUNCTION_H
#define SQLFUNCTION_H
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include "data_linear.h"
#include <QStringList>
#include "QStringLiteral.h"

//数据库处理程序

class SqlFunction
{
    static QSqlQuery* query;
public:

    static QSqlDatabase db;
    SqlFunction()=delete;
    //数据库连接相关接口
    static bool create_connection();//连接数据库

    //用户信息相关接口
    static QString name;//用户名
    static QString id;//用户id
    static QString person_type;//用户类型
    static bool set_name(QString name);
    static bool person_name_valid(QString name);//判断新账户名的合法性
    static bool person_name_unique(QString name);//判断姓名是否唯一
    static bool add_person(QString name, QString password, QString person_type);//添加用户
    static bool get_person_id_from_name(QString name, QString& id);
    static bool get_person_name_from_id(QString id, QString& name);
    static bool get_person_type_from_id();//判断是普通用户还是管理员
    static bool login(QString name, QString password);//登录
    static bool password_change(QString name, QString password);//更改密码
    static bool get_name(QString& name);

    //收藏夹相关接口
    static bool get_folder_root(QString& folder_root_id, QString person_id);
    static bool get_child_leaves(QString folder_id, data_linear& data_child, data_linear& data_leaves);
    static bool get_child_folder(QString folder_id, data_linear& data);
    static bool get_leaves(QString folder_id, data_linear& data);
    static bool folder_delete(QString folder_id);
    static void folder_delete_DFS(QString folder_id);
    static bool folder_leaves_delete(QString folder_id);
    static bool folder_higher(QString folder_id1, QString folder_id2);
    static bool folder_move(QString folder_id, QString father_id, QString new_father_id);
    static bool add_folder(QString name,QString root_folder_id);
    static bool add_leaves(QString book_id, QString root_folder_id);

    //图书检索及管理相关接口
    static bool book_retrieve(data_linear* data_new,QStringList& param);
    static bool book_record_delete_all(int id);
    static int add_book_record(QStringList &param);
    static QString load_e_book(QString& book_id);
    static bool load_book_info(data_linear* data,QString book_id);
    static int update_book_info(QString book_id,QString num_total,QString abstraction);
    static bool latest_book_retrieve(data_linear* data);

    //图书借阅相关接口
    static int book_borrow(QString book_id, QString time_borrow, QString time_return);//提交借书申请
    static int book_borrow_check(QString& book_id,QString& name_id, QString action);//借书审批
    static bool load_book_borrow_application_for_admin(data_linear* data,QStringList& param);//加载所有未审核的图书申请，供管理员审核
    static bool load_book_unreturned_for_admin(data_linear* data,QStringList& param);//加载所有未还的图书，供管理员选择设为归还
    static int book_return(QString book_id, QString person_id);//设置图书为已归还
    static bool load_book_borrow_current_state_for_user(data_linear* data);
    static bool load_book_borrow_history_for_user(data_linear* data);

    //读者管理相关接口
    static bool reader_retrieve(data_linear *data, QStringList &param);
    static int delete_reader(QString& reader_id);

    //消息相关接口
    static bool get_message_list(QString person_id, data_linear& data);//获取消息列表
    static bool send_message(QString sender_id, QString receiver_id, QString content);//发送消息
    static bool send_message(QString sender_id, QString receiver_id, QString content, QString father_id);//回复消息

private:
    //系统日志相关接口
    static bool get_system_time(QString& now);
    static bool add_thing(QString verb, QString thing_type);

    //data_linear处理相关接口
    static bool load_data_linear(data_linear& data, QSqlQuery& query, int column_start, int column_end);//向data中装载query的数据
    static bool write_data_linear(data_linear& data, QSqlQuery* query, int row_start, int row_end, int column_start, int column_end);//向data指定区域写入数据


    //insert语句相关接口
    static void item_add_1(QString table_name, QString arg1);
    static void item_add_2(QString table_name, QString arg1, QString arg2);
    static void item_add_3(QString table_name, QString arg1, QString arg2, QString arg3);
    static void item_add_4(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4);
    static void item_add_5(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5);
    static void item_add_6(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6);
    static void item_add_9(QString table_name, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, QString arg7, QString arg8, QString arg9);
    //update语句相关接口
    static void item_update_1(QString table_name, QString prop, QString new_data, QString prop1, QString val1);
    static void item_update_2(QString table_name, QString prop, QString new_data, QString prop1, QString val1, QString prop2, QString val2);

    //delete语句相关接口
    static void item_delete_1(QString table_name, QString prop1, QString val1);

    //id管理相关接口
    static void get_new_id(QString table_name, QString& new_id, QString type_name);//为某个类型分配1个新的编号,如thing
    static void get_new_id_multilple(QString table_name, QString &new_id, QString type_name,QString& count);//为某个类型分配多个新的编号,如book_object
    static bool type_check(QString table_name, QString id, QString type_name);

    //文本处理相关接口
    static QString add_quotation(QString content);
};

#endif // SQLFUNCTION_H
