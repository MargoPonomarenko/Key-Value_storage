QT += testlib
QT -= gui
QT += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_keyvaluestoragetest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Key-Value_Storage-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/release/ -lKey-Value_storage

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Key-Value_Storage-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/debug/ -lKey-Value_storage

else:unix: LIBS += -L/home/runner/work/Key-Value_storage/Key-Value_storage/KeyStorageTest/ -lKey-Value_storage

INCLUDEPATH += "../"

DEPENDPATH += $$PWD/ release
