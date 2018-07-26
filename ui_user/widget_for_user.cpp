#include "widget_for_user.h"
#include "ui_widget_for_user.h"
#include "ui_user/managebookwindow_for_user.h"
#include "ui_user/homepage_for_user.h"
#include "utilTool/QStringLiteral.h"
#include "ui_user/borrowingmanagement_for_user.h"
#include <QLabel>
#include <QMainWindow>
#include <QTableWidget>
#include <cstring>
#include <QPainter>
#include <QProxyStyle>
#include <QSize>
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 90; // 设置每个tabBar中item的大小
            s.rheight() = 44;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

Widget_For_User::Widget_For_User(QTabWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Widget_For_User)
{
    HomePage_For_User *homepage=new HomePage_For_User();
    ManageBookWindow_For_User* manageBookWindow=new ManageBookWindow_For_User();
    //FavouriteList_For_User *myfavoritelist=new FavouriteList_For_User();
    BorrowingManagement_For_User *myborrowing=new BorrowingManagement_For_User();
    //Mytalks *mytalks=new Mytalks();
    //Myalert *myalert=new Myalert();
    this->addTab(homepage,QStringLiteral("主页"));
    this->addTab(manageBookWindow,QStringLiteral("检索图书"));
    //this->addTab(myfavoritelist,QStringLiteral("收藏夹"));
    this->addTab(myborrowing,QStringLiteral("图书借还"));
    //this->addTab(mytalks,QStringLiteral("mytalk"));
    //this->addTab(myalert,QStringLiteral("myalert"));
    this->setTabPosition(QTabWidget::West);
    this->tabBar()->setStyle(new CustomTabStyle);
    ui->setupUi(this);
    this->setMinimumSize(QSize(1250,731));
    this->setMaximumSize(QSize(1250,731));
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QObject::connect(this,SIGNAL(init()),manageBookWindow,SLOT(load_all_book()));
    QObject::connect(this,SIGNAL(init()),homepage,SLOT(load_latest_book()));
    QObject::connect(this,SIGNAL(init()),myborrowing,SLOT(load()));
}

Widget_For_User::~Widget_For_User()
{
    delete ui;
}

void Widget_For_User::login(QString name){
    this->show();
    emit init();
}
