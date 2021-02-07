#-------------------------------------------------
#
# Project created by QtCreator 2019-08-03T15:16:40
#
#-------------------------------------------------

QT       += core gui webenginewidgets webengine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Browser
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

HEADERS += \
    Addons/Permissions/featurepermissinwidget.h \
    Addons/Permissions/permissionswidget.h \
    Addons/Permissions/permissionswidgetitem.h \
    Addons/RightPanel/Console/console.h \
    Addons/RightPanel/Console/consoleeditor.h \
    Addons/RightPanel/qwe.h \
    Addons/Scripts/script.h \
    Addons/Scripts/scriptspanel.h \
    Addons/Tabs/actionpanel.h \
    Addons/Tabs/closetabhistory.h \
    Addons/Tabs/tab.h \
    Addons/Tabs/tabloadicon.h \
    Addons/Tabs/tabslayout.h \
    Addons/Tabs/tabspanel.h \
    Addons/viewport.h \
    Addons/webpage.h \
    Addons/webpageinfo.h \
    Addons/window.h \
    Inhernit/consolemessage.h \
    Inhernit/consoletextedit.h \
    Inhernit/qstandartwidget.h \
    Inhernit/urlcompletteritem.h \
    Inhernit/urllineedit.h

SOURCES += main.cpp \
    Addons/Permissions/featurepermissinwidget.cpp \
    Addons/Permissions/permissionswidget.cpp \
    Addons/Permissions/permissionswidgetitem.cpp \
    Addons/RightPanel/Console/console.cpp \
    Addons/RightPanel/Console/consoleeditor.cpp \
    Addons/RightPanel/qwe.cpp \
    Addons/Scripts/script.cpp \
    Addons/Scripts/scriptspanel.cpp \
    Addons/Tabs/actionpanel.cpp \
    Addons/Tabs/closetabhistory.cpp \
    Addons/Tabs/tab.cpp \
    Addons/Tabs/tabloadicon.cpp \
    Addons/Tabs/tabslayout.cpp \
    Addons/Tabs/tabspanel.cpp \
    Addons/viewport.cpp \
    Addons/webpage.cpp \
    Addons/webpageinfo.cpp \
    Addons/window.cpp \
    Inhernit/consolemessage.cpp \
    Inhernit/consoletextedit.cpp \
    Inhernit/qstandartwidget.cpp \
    Inhernit/urlcompletteritem.cpp \
    Inhernit/urllineedit.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    docs.qrc
