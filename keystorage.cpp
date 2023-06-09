#include "keystorage.h"
#include <QDebug>


KeyStorage::KeyStorage()
{
    storageModel = new KeyStorageModel;
    backupService = new SQLiteBackupService;
    timer = new QTimer;
    backupService->setStorage(this);
    backupService->initSlotConnection();
    connect(backupService, &SQLiteBackupService::dataLoaded, this, &KeyStorage::onDataLoaded);
    connect(timer, &QTimer::timeout, this, &KeyStorage::clearStorage);
    timer->moveToThread(&timerThread);
    connect(&timerThread, &QThread::finished, timer, &QObject::deleteLater);
    timerThread.start();
    timer->start(1000);

}

KeyStorage::~KeyStorage()
{
    timerThread.quit();
    timerThread.wait();
}

void KeyStorage::put(QString key, QString value)
{
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
    qDebug()<<"onDataLoaded func"<<value<<" by key: "<<key;

    switch(value->itemType)
    {
    case DataType::qString:
        qDebug()<<"Catch in QSting "<<((StringItem *)value)->data;
        emit gettedString(((StringItem *)value)->data);
        break;
    case DataType::doubleValue:
        qDebug()<<"Catch in double";
        emit gettedDouble(((DoubleItem *)value)->data);
        break;
    case DataType::qStringVector:
        qDebug()<<"Catch in vector";
        emit gettedVectorString(((VectorStringItem *)value)->data);
        break;
    default:
        qDebug()<<"Catch in default";
        break;
    }
}

void KeyStorage::clearStorage()
{
    qDebug()<<"Clear Storage";
}
