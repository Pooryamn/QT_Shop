#-------------------------------------------------
#
# Project created by QtCreator 2020-03-02T20:18:13
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB_Shop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        cart.cpp \
        employee_part.cpp \
        forget.cpp \
        gateway.cpp \
        help.cpp \
        loging.cpp \
        main.cpp \
        master_part.cpp \
        master_signup.cpp \
        new_stock.cpp \
        shop_history.cpp \
        signup.cpp \
        suppliers.cpp \
        user_edit.cpp \
        user_part.cpp \
        user_payment.cpp \
        users.cpp \
        verify_employee.cpp \
        verify_user.cpp \
        widget.cpp

HEADERS += \
        cart.h \
        employee_part.h \
        forget.h \
        gateway.h \
        help.h \
        loging.h \
        master_part.h \
        master_signup.h \
        new_stock.h \
        shop_history.h \
        signup.h \
        suppliers.h \
        user_edit.h \
        user_part.h \
        user_payment.h \
        users.h \
        verify_employee.h \
        verify_user.h \
        widget.h

FORMS += \
        cart.ui \
        employee_part.ui \
        forget.ui \
        gateway.ui \
        help.ui \
        loging.ui \
        master_part.ui \
        master_signup.ui \
        new_stock.ui \
        shop_history.ui \
        signup.ui \
        suppliers.ui \
        user_edit.ui \
        user_part.ui \
        user_payment.ui \
        users.ui \
        verify_employee.ui \
        verify_user.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
