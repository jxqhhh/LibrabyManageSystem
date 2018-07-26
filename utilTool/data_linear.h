#ifndef DATA_LINEAR_H
#define DATA_LINEAR_H
#include <list>
#include <vector>
#include <QString>
#include <QStringList>
class data_linear
{
public:
    data_linear();
    ~data_linear();
    bool initialized;
    bool initialize(int row_num,int column_num, int display_column_start, int display_column_end);
    bool initialize(int column_num, int display_conlumn_start, int display_column_end);
    bool clear();
    bool empty();
    bool add_content(QString content,int row,int column);
    bool add_content(QString content,int column);
    QString get_content(int row, int column);
    bool add_row();
    bool add_column(QString value="");
    int get_row_num();
    int get_column_num();
    bool remove_row(int row);
    QStringList get_horizontal_labels();
    bool set_horizontal_labels(QStringList& horizontal_labels);
    bool add_horizontal_label(QString label);
    bool row_valid(int row);
    bool row_valid(int row_start, int row_end);
    bool column_valid(int column);
    bool column_valid(int column_start, int column_end);
    void print();//调试用

    int row_num;//行数
    int column_num;//列数
    int display_column_start;
    int display_column_end;
private:

    QStringList horizontal_labels;
    //std::vector<data_linear*> children;
    std::vector<QString>* column_name;
    std::vector<std::vector<QString>*>* rows;
};

#endif // DATA_LINEAR_H
