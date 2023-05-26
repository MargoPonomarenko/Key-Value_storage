#include "keystorage.h"

KeyStorage::KeyStorage()
{

}

void KeyStorage::put(QString key, QString value)
{
    StringItem item{{DataType::qString}, value};
    put(key, item);
}

void KeyStorage::put(QString key, double value)
{

}

void KeyStorage::put(QString key, QVector<QString> value)
{

}

void KeyStorage::put(QString key, StorageItem value)
{
    KeyStorage::storageModel.put(key, value);
}
