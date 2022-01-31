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
    main.cpp \
    maindashboard.cpp \
    mainwindow.cpp \
    newtaskform.cpp \
    registerform.cpp \
    task.cpp \
    taskdelegate.cpp \
    user.cpp \
    validator.cpp

HEADERS += \
    authenticationservice.h \
    dataservice.h \
    loginform.h \
    maindashboard.h \
    mainwindow.h \
    newtaskform.h \
    registerform.h \
    task.h \
    taskdelegate.h \
    user.h \
    validator.h

FORMS += \
    loginform.ui \
    maindashboard.ui \
    mainwindow.ui \
    mainwindow.ui \
    newtaskform.ui \
    registerform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
