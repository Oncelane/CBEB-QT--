QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customadd.cpp \
    customedit.cpp \
    custommanage.cpp \
    goodadd.cpp \
    goodedit.cpp \
    goodmanage.cpp \
    homepage.cpp \
    loginpage.cpp \
    main.cpp \
    mainwindow.cpp \
    orderadd.cpp \
    ordermanage.cpp \
    simpleeditpage.cpp \
    stashadd.cpp \
    stashandgoodpage.cpp \
    stashmanage.cpp \
    supplieradd.cpp \
    supplieredit.cpp \
    suppliermanage.cpp

HEADERS += \
    customadd.h \
    customedit.h \
    custommanage.h \
    goodadd.h \
    goodedit.h \
    goodmanage.h \
    homepage.h \
    loginpage.h \
    mainwindow.h \
    orderadd.h \
    ordermanage.h \
    simpleeditpage.h \
    sqlhead.h \
    stashadd.h \
    stashandgoodpage.h \
    stashmanage.h \
    supplieradd.h \
    supplieredit.h \
    suppliermanage.h

FORMS += \
    customadd.ui \
    customedit.ui \
    custommanage.ui \
    goodadd.ui \
    goodedit.ui \
    goodmanage.ui \
    homepage.ui \
    loginpage.ui \
    mainwindow.ui \
    orderadd.ui \
    ordermanage.ui \
    simpleeditpage.ui \
    stashadd.ui \
    stashandgoodpage.ui \
    stashmanage.ui \
    supplieradd.ui \
    supplieredit.ui \
    suppliermanage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource/res.qrc

DISTFILES += \
    text.txt
