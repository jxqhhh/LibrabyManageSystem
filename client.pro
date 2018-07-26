#-------------------------------------------------
#
# Project created by QtCreator 2018-05-30T19:58:36
#
#-------------------------------------------------

QT       += core gui sql
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    logger.cpp \
    utilTool/data_linear.cpp \
    utilTool/sqlfunction.cpp \
    utilTool/string_to_int_tool.cpp \
    utilTool/manager/book_retrieve_manager.cpp \
    ui_administrator/addbookdialog_for_admin.cpp \
    ui_administrator/addreaderdialog_for_admin.cpp \
    ui_administrator/auditwindow_for_admin.cpp \
    ui_administrator/helpdialog_for_admin.cpp \
    ui_administrator/managebookwindow_for_admin.cpp \
    ui_administrator/managereaderwindow_for_admin.cpp \
    ui_administrator/widget_for_admin.cpp \
    ui_user/managebookwindow_for_user.cpp \
    ui_user/widget_for_user.cpp \
    ui_user/homepage_for_user.cpp \
    ui_user/borrowingmanagement_for_user.cpp \
    utilTool/manager/book_borrow_manager.cpp \
    ui_user/set_loan_period_dialog.cpp \
    utilTool/manager/reader_retrieve_manager.cpp \
    ui_common/book_preview_dlg.cpp \
    ui_administrator/changebookinfodlg_for_admin.cpp \
    utilTool/display_tool/displayfunction.cpp \
    utilTool/display_tool/display_for_managebookwindow_for_admin.cpp \
    utilTool/display_tool/display_for_managebookwindow_for_user.cpp \
    utilTool/display_tool/display_for_auditwindow_bookborrow_for_admin.cpp \
    utilTool/display_tool/display_for_auditwindow_bookreturn_for_admin.cpp \
    utilTool/display_tool/display_for_managereader_window_for_admin.cpp \
    utilTool/display_tool/display_default.cpp \
    ui_common/new_account_apply.cpp

HEADERS  += \
    logger.h \
    utilTool/data_linear.h \
    utilTool/QStringLiteral.h \
    utilTool/sqlfunction.h \
    utilTool/string_to_int_tool.h \
    utilTool/manager/book_retrieve_manager.h \
    ui_administrator/addbookdialog_for_admin.h \
    ui_administrator/addreaderdialog_for_admin.h \
    ui_administrator/auditwindow_for_admin.h \
    ui_administrator/helpdialog_for_admin.h \
    ui_administrator/managebookwindow_for_admin.h \
    ui_administrator/managereaderwindow_for_admin.h \
    ui_administrator/widget_for_admin.h \
    ui_user/managebookwindow_for_user.h \
    ui_user/widget_for_user.h \
    ui_user/homepage_for_user.h \
    ui_user/borrowingmanagement_for_user.h \
    utilTool/manager/book_borrow_manager.h \
    ui_user/set_loan_period_dialog.h \
    utilTool/manager/reader_retrieve_manager.h \
    ui_common/book_preview_dlg.h \
    ui_administrator/changebookinfodlg_for_admin.h \
    utilTool/display_tool/displayfunction.h \
    utilTool/display_tool/display_for_managebookwindow_for_admin.h \
    utilTool/display_tool/display_for_managebookwindow_for_user.h \
    utilTool/display_tool/display_for_auditwindow_bookborrow_for_admin.h \
    utilTool/display_tool/display_for_auditwindow_bookreturn_for_admin.h \
    utilTool/display_tool/display_for_managereader_window_for_admin.h \
    utilTool/display_tool/display_default.h \
    ui_common/new_account_apply.h

FORMS    += \
    logger.ui \
    ui_administrator/addbookdialog_for_admin.ui \
    ui_administrator/addreaderdialog_for_admin.ui \
    ui_administrator/auditwindow_for_admin.ui \
    ui_administrator/helpdialog_for_admin.ui \
    ui_administrator/managebookwindow_for_admin.ui \
    ui_administrator/managereaderwindow_for_admin.ui \
    ui_administrator/widget_for_admin.ui \
    ui_user/managebookwindow_for_user.ui \
    ui_user/widget_for_user.ui \
    ui_user/homepage_for_user.ui \
    ui_user/borrowingmanagement_for_user.ui \
    ui_user/set_loan_period_dialog.ui \
    ui_common/book_preview_dlg.ui \
    ui_administrator/changebookinfodlg_for_admin.ui \
    ui_common/new_account_apply.ui

DISTFILES +=
