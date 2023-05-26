#ifndef KEYSTORAGE_H
#define KEYSTORAGE_H

#include "keyStorageModel.h"


class KeyStorage
{
public:
    KeyStorage();
    static void put(QString key, QString value);
    static void put(QString key, double value);
    static void put(QString key, QVector<QString> value);
private:
    static KeyStorageModel storageModel;
    static void put(QString key, StorageItem value);
};

#endif // KEYSTORAGE_H
