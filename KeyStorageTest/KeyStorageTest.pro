QT += testlib
QT -= gui
QT += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_keyvaluestoragetest.cpp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Key-Value_Storage-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/release/ -lKey-Value_storage

#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Key-Value_Storage-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/debug/ -lKey-Value_storage

unix: LIBS += -L$$PWD/../ -lKey-Value_Storage

INCLUDEPATH += $$PWD/../

DEPENDPATH += $$PWD/../
