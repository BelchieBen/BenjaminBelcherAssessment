QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authenticationservice.cpp \
    dataservice.cpp \
    loginform.cpp \
    loginlandingpage.cpp \
    main.cpp \
    maindashboard.cpp \
    mainwindow.cpp \
    newprojectform.cpp \
    newtaskform.cpp \
    otherprojectsdialog.cpp \
    profile.cpp \
    projectbtn.cpp \
    projectdataservice.cpp \
    registerform.cpp \
    task.cpp \
    taskdataservice.cpp \
    taskdelegate.cpp \
    taskstates.cpp \
    user.cpp \
    validator.cpp

HEADERS += \
    authenticationservice.h \
    dataservice.h \
    loginform.h \
    loginlandingpage.h \
    maindashboard.h \
    mainwindow.h \
    newprojectform.h \
    newtaskform.h \
    otherprojectsdialog.h \
    profile.h \
    projectbtn.h \
    projectdataservice.h \
    registerform.h \
    task.h \
    taskdataservice.h \
    taskdelegate.h \
    taskstates.h \
    user.h \
    validator.h

FORMS += \
    loginform.ui \
    loginlandingpage.ui \
    maindashboard.ui \
    mainwindow.ui \
    mainwindow.ui \
    newprojectform.ui \
    newtaskform.ui \
    otherprojectsdialog.ui \
    profile.ui \
    registerform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
