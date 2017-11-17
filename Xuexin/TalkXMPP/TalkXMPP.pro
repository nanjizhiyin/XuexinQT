#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T16:30:35
#
#-------------------------------------------------

include(../qxmpp/qxmpp.pri)


QT       += core gui sql network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalkXMPP
TEMPLATE = app

QMAKE_LIBDIR += ../qxmpp/src
QMAKE_RPATHDIR += $$OUT_PWD/../qxmpp/src
INCLUDEPATH += $$PWD $$QXMPP_INCLUDEPATH
LIBS += $$QXMPP_LIBS


INCLUDEPATH += login \
    utils \
    manager \
    view \
    view/Info \
    view/Friend \
    view/Group \
    view/SNS \
    view/More \
    manager/SQL \
    view/Chat


SOURCES += main.cpp\
        mainwindow.cpp \
    utils/Utils.cpp \
    manager/ViewManager.cpp \
    view/Info/InfoWidget.cpp \
    manager/XmppManager.cpp \
    manager/SQL/SQLManager.cpp \
    manager/SQL/SQLMember.cpp \
    manager/SQL/SQLFriend.cpp \
    view/RootWidget.cpp \
    login/LoginWidget.cpp \
    view/Group/GroupWidget.cpp \
    view/Friend/FriendWidget.cpp \
    view/Friend/FriendCell.cpp \
    view/SNS/SNSWidget.cpp \
    manager/SignalManager.cpp \
    view/Chat/ChatWidget.cpp \
    view/More/MoreWidget.cpp \
    manager/SQL/SQLMsgHistory.cpp \
    view/Chat/chatcell.cpp

HEADERS  += mainwindow.h \
    utils/Utils.h \
    manager/ViewManager.h \
    view/Info/InfoWidget.h \
    manager/XmppManager.h \
    manager/SQL/SQLManager.h \
    manager/SQL/SQLMember.h \
    manager/SQL/SQLFriend.h \
    view/RootWidget.h \
    login/LoginWidget.h \
    view/Group/GroupWidget.h \
    view/Friend/FriendWidget.h \
    view/Friend/FriendCell.h \
    view/SNS/SNSWidget.h \
    manager/SignalManager.h \
    view/Chat/ChatWidget.h \
    view/More/MoreWidget.h \
    manager/SQL/SQLMsgHistory.h \
    manager/EnumManager.h \
    view/Chat/chatcell.h

FORMS    += mainwindow.ui

QMAKE_MAC_SDK = macosx10.9

RESOURCES += \
    images.qrc
