#ifndef KEYSTORAGE_H
#define KEYSTORAGE_H

#if defined MAKE_TEST_LIB
    #define TEST_LIB_EXPORT Q_DECL_EXPORT
#else
    #define TEST_LIB_EXPORT Q_DECL_IMPORT
#endif

#include "keyStorageModel.h"

class KeyStorage
{
public:
    KeyStorage();
    static KeyStorageModel * storageModel;

    static void put(QString key, QString value);
    static void put(QString key, double value);
    static void put(QString key, QVector<QString> value);

    static QString getString(QString key);
    static double getDouble(QString key);
    static QVector<QString> getStringVector(QString key);

    static QString patch(QString key, QString newValue);
    static double patch(QString key, double newValue);
    static QVector<QString> patch(QString key, QVector<QString> newValue);

    void remove(QString key);
private:
    static void put(QString key, StorageItem *value);
};

#endif // KEYSTORAGE_H
