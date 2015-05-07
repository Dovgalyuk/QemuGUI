#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T16:36:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QEMU-GUI
TEMPLATE = app


SOURCES += Main.cpp\
    QTableViewCheckBox.cpp \
    NetNicWidget.cpp \
    NetUserWidget.cpp \
    LineEditWithLabel.cpp \
    CheckBoxWithLabel.cpp \
    NetTapWidget.cpp \
    NetAbstractWidget.cpp \
    ChooseObjectWidget.cpp \
    NetTreeWidget.cpp \
    QDNetConfiguration.cpp \
    QEMUSettings.cpp \
    ConfTreeWidget.cpp \
    QDDeleteObject.cpp \
    QDSetName.cpp \
    QEMUGlobalSettings.cpp \
    VMProperties.cpp \
    QEMU-GUI.cpp \
    VMPropertiesDialog.cpp \
    VMRunner.cpp \
    ReplayOptionsDialog.cpp \
    GlobalSettingsDialog.cpp \
    DrivePropertiesDialog.cpp

HEADERS  += \
    QTableViewCheckBox.h \
    NetNicWidget.h \
    NetUserWidget.h \
    LineEditWithLabel.h \
    CheckBoxWithLabel.h \
    NetTapWidget.h \
    NetAbstractWidget.h \
    ChooseObjectWidget.h \
    NetTreeWidget.h \
    QDNetConfiguration.h \
    QEMUSettings.h \
    ConfTreeWidget.h \
    QDDeleteObject.h \
    QDSetName.h \
    QEMUGlobalSettings.h \
    VMProperties.h \
    QEMU-GUI.h \
    VMPropertiesDialog.h \
    VMRunner.h \
    ReplayOptionsDialog.h \
    GlobalSettingsDialog.h \
    DrivePropertiesDialog.h

FORMS    += \
    VMPropertiesDialog.ui \
    ReplayOptionsDialog.ui \
    GlobalSettingsDialog.ui \
    MainWindow.ui \
    DrivePropertiesDialog.ui

RESOURCES += \
    QEMU-GUI.qrc
