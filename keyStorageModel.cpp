#include "keyStorageModel.h"

#include "QDebug"

KeyStorageModel::KeyStorageModel():storage(*new QMap<QString, StorageItem *>)
{
    KeyStorageModel::setTimeLife(3);
}

KeyStorageModel::~KeyStorageModel()
{
    storage.clear();
    for(QString const &item:storage.keys()){
        delete storage[item];
    }
    delete &storage;

}

void KeyStorageModel::put(QString key, StorageItem * value)
{
    storage[key] = value;
    qDebug()<<"Data put into model";
}

StorageItem *KeyStorageModel::get(QString key)
{
    if (storage.contains(key)) {
        return storage[key];
    }
    return nullptr;
}

void KeyStorageModel::patch(QString key, StorageItem *newValue)
{
    if (storage.contains(key)) {
        storage[key] = newValue;
    }
}

void KeyStorageModel::remove(QString key)
{
    storage.remove(key);
}

void KeyStorageModel::setTimeLife(int days)
{
    timeLife = days;
}

void KeyStorageModel::removeOld()
{
    for(QString const &item:storage.keys()){
        if(storage[item]->created.daysTo(QDate()) > timeLife){
            storage.remove(item);
        }
    }
}

