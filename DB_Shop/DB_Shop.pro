#-------------------------------------------------
#
# Project created by QtCreator 2020-03-02T20:18:13
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

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
        database.cpp \
        employee_part.cpp \
        favorites.cpp \
        forget.cpp \
        gateway.cpp \
        help.cpp \
        loging.cpp \
        mail/emailaddress.cpp \
        mail/mimeattachment.cpp \
        mail/mimecontentformatter.cpp \
        mail/mimefile.cpp \
        mail/mimehtml.cpp \
        mail/mimeinlinefile.cpp \
        mail/mimemessage.cpp \
        mail/mimemultipart.cpp \
        mail/mimepart.cpp \
        mail/mimetext.cpp \
        mail/quotedprintable.cpp \
        mail/smtpclient.cpp \
        main.cpp \
        master_part.cpp \
        master_signup.cpp \
        new_stock.cpp \
        new_supplier.cpp \
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
        database.h \
        employee_part.h \
        favorites.h \
        forget.h \
        gateway.h \
        help.h \
        loging.h \
        mail/SmtpMime \
        mail/emailaddress.h \
        mail/mimeattachment.h \
        mail/mimecontentformatter.h \
        mail/mimefile.h \
        mail/mimehtml.h \
        mail/mimeinlinefile.h \
        mail/mimemessage.h \
        mail/mimemultipart.h \
        mail/mimepart.h \
        mail/mimetext.h \
        mail/quotedprintable.h \
        mail/smtpclient.h \
        mail/smtpexports.h \
        master_part.h \
        master_signup.h \
        new_stock.h \
        new_supplier.h \
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
        favorites.ui \
        forget.ui \
        gateway.ui \
        help.ui \
        loging.ui \
        master_part.ui \
        master_signup.ui \
        new_stock.ui \
        new_supplier.ui \
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
