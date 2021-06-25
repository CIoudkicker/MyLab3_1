QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT += charts

TARGET = WidgetCheck
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalculateSize_TableModel.cpp \
    Context_CalculateSize.cpp \
    Context_Diagrams.cpp \
    Folder_CalculateSize.cpp \
    ICalculateSize.cpp \
    IObserver.cpp \
    ISubject.cpp \
    Type_CalculateSize.cpp \
    diagramwidgets.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CalculateSize_TableModel.h \
    Context_CalculateSize.h \
    Context_Diagrams.h \
    Folder_CalculateSize.h \
    ICalculateSize.h \
    IObserver.h \
    ISubject.h \
    Type_CalculateSize.h \
    diagramwidgets.h \
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
