#include "keystorage.h"
#include <QDebug>

KeyStorage::KeyStorage()
{
    storageModel = new KeyStorageModel;
    backupService = new SQLiteBackupService;
    backupService->setStorage(this);
    backupService->initSlotConnection();
    connect(backupService, &SQLiteBackupService::dataLoaded, this, &KeyStorage::onDataLoaded);
}

void KeyStorage::put(QString key, QString value)
{
    qDebug()<<"In put method";
    StringItem *item = new StringItem {DataType::qString, QDate::currentDate(), value};
    put(key, item);
    qDebug()<<"Emit signal saveToDatabase";
    emit saveToDatabase(key, item);
}

void KeyStorage::put(QString key, double value)
{
    DoubleItem *item = new DoubleItem {DataType::doubleValue, QDate::currentDate(), value};
    put(key, item);
    emit saveToDatabase(key, item); //для типу double
}

void KeyStorage::put(QString key, QVector<QString> value)
{
    VectorStringItem *item = new VectorStringItem {DataType::qStringVector, QDate::currentDate(), value};
    put(key, item);
    emit saveToDatabase(key, item); //для типу string vector
}

void KeyStorage::put(QString key, StorageItem * value)
{
    qDebug()<<"In MAIN put method";
    KeyStorage::storageModel->put(key, value);
}


void KeyStorage::getString(QString key)
{
    StringItem *item = (StringItem *)KeyStorage::storageModel->get(key);
    if(item == nullptr){
        emit loadFromDatabase(key);
    }
    else{
       emit gettedString(item->data);
    }
}

void KeyStorage::getDouble(QString key)
{
    DoubleItem *item = (DoubleItem *)KeyStorage::storageModel->get(key);
    if(item == nullptr){
        emit loadFromDatabase(key);
    }
    else{
       emit gettedDouble(item->data);
    }
}

void KeyStorage::getStringVector(QString key)
{
    VectorStringItem *item = (VectorStringItem *)KeyStorage::storageModel->get(key);
    if(item == nullptr){
        emit loadFromDatabase(key);
    }
    else{
       emit gettedVectorString(item->data);
    }
}

bool KeyStorage::patch(QString key, QString newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        StringItem *item = (StringItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
        return true;
    }
    return false;
}

bool KeyStorage::patch(QString key, double newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        DoubleItem *item = (DoubleItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
        return true;
    }
    return false;
}

bool KeyStorage::patch(QString key, QVector<QString> newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        VectorStringItem *item = (VectorStringItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
        return true;
    }
    return false;
}

void KeyStorage::remove(QString key)
{
    KeyStorage::storageModel->remove(key);
}

void KeyStorage::onDataLoaded(QString key, StorageItem *value)
{
    qDebug()<<"onDataLoaded func"<<(int)(value->itemType);

    switch(value->itemType)
    {
    case DataType::qString:

        emit gettedString("test line");
        //emit gettedString(((StringItem *)value)->data);
        break;
    case DataType::doubleValue:
        emit gettedDouble(((DoubleItem *)value)->data);
        break;
    case DataType::qStringVector:
        emit gettedVectorString(((VectorStringItem *)value)->data);
        break;

    }
}
