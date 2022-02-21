QT += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    delegates/commentdelegate.cpp \
    delegates/messagedelegate.cpp \
    delegates/taskdelegate.cpp \
    delegates/tasksearchresultdelegate.cpp \
    globals/emailserverdetails.cpp \
    globals/taskstates.cpp \
    globals/userroles.cpp \
    main.cpp \
    mainwindow.cpp \
    models/projectmessage.cpp \
    models/task.cpp \
    models/taskcomment.cpp \
    models/user.cpp \
    services/authenticationservice.cpp \
    services/dataservice.cpp \
    services/emailservice.cpp \
    services/projectdataservice.cpp \
    services/taskdataservice.cpp \
    utils/time.cpp \
    utils/validator.cpp \
    views/forms/loginform.cpp \
    views/forms/newprojectform.cpp \
    views/forms/newtaskform.cpp \
    views/forms/otherprojectsdialog.cpp \
    views/forms/registerform.cpp \
    views/loginlandingpage.cpp \
    views/maindashboard.cpp \
    views/profile.cpp \
    views/projectchat.cpp \
    views/projectsettingspage.cpp \
    views/quickloginpage.cpp \
    views/searchtasksallprojectsdialog.cpp \
    views/taskdetails.cpp

HEADERS += \
    delegates/commentdelegate.h \
    delegates/messagedelegate.h \
    delegates/taskdelegate.h \
    delegates/tasksearchresultdelegate.h \
    globals/emailserverdetails.h \
    globals/taskstates.h \
    globals/userroles.h \
    mainwindow.h \
    models/projectmessage.h \
    models/task.h \
    models/taskcomment.h \
    models/user.h \
    services/authenticationservice.h \
    services/dataservice.h \
    services/emailservice.h \
    services/projectdataservice.h \
    services/taskdataservice.h \
    utils/time.h \
    utils/validator.h \
    views/forms/loginform.h \
    views/forms/newprojectform.h \
    views/forms/newtaskform.h \
    views/forms/otherprojectsdialog.h \
    views/forms/registerform.h \
    views/loginlandingpage.h \
    views/maindashboard.h \
    views/profile.h \
    views/projectchat.h \
    views/projectsettingspage.h \
    views/quickloginpage.h \
    views/searchtasksallprojectsdialog.h \
    views/taskdetails.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui \
    views/forms/loginform.ui \
    views/forms/newprojectform.ui \
    views/forms/newtaskform.ui \
    views/forms/otherprojectsdialog.ui \
    views/forms/registerform.ui \
    views/loginlandingpage.ui \
    views/maindashboard.ui \
    views/profile.ui \
    views/projectchat.ui \
    views/projectsettingspage.ui \
    views/quickloginpage.ui \
    views/searchtasksallprojectsdialog.ui \
    views/taskdetails.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
