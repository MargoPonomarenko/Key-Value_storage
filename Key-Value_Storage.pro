QT -= gui
QT += sql
QT += testlib
QT += core

TEMPLATE = lib
#TEMPLATE = subdirs
DEFINES += KEYVALUESTORAGE_LIBRARY
CONFIG += c++17
#SUBDIRS = KeyStorageTest/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    keyStorageModel.cpp \
    keystorage.cpp \
    sqlitebackupservice.cpp

HEADERS += \
    KeyValueStorage_global.h \
    keyStorageModel.h \
    keystorage.h \
    sqlitebackupservice.h


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
