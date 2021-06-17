QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalculateSize_TableModel.cpp \
    Context.cpp \
    Folder_CalculateSize.cpp \
    ICalculateSize.cpp \
    Type_CalculateSize.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CalculateSize_TableModel.h \
    Context.h \
    Folder_CalculateSize.h \
    ICalculateSize.h \
    Type_CalculateSize.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    MyLab3_1.pro.user \
    README.md
