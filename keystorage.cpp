#include "keystorage.h"

KeyStorageModel * KeyStorage::storageModel = new KeyStorageModel;

KeyStorage::KeyStorage()
{
}

void KeyStorage::put(QString key, QString value)
{
    StringItem *item = new StringItem {DataType::qString, QDate::currentDate(), value};
    put(key, item);
}

void KeyStorage::put(QString key, double value)
{
    DoubleItem *item = new DoubleItem {DataType::doubleValue, QDate::currentDate(), value};
    put(key, item);
}

void KeyStorage::put(QString key, QVector<QString> value)
{
    VectorStringItem *item = new VectorStringItem {DataType::qStringVector, QDate::currentDate(), value};
    put(key, item);
}

void KeyStorage::put(QString key, StorageItem * value)
{
    KeyStorage::storageModel->put(key, value);
}


QString KeyStorage::getString(QString key)
{
    return ((StringItem *)KeyStorage::storageModel->get(key))->data;
}

double KeyStorage::getDouble(QString key)
{
    return ((DoubleItem *)KeyStorage::storageModel->get(key))->data;
}

QVector<QString> KeyStorage::getStringVector(QString key)
{
    return ((VectorStringItem *)KeyStorage::storageModel->get(key))->data;
}

QString KeyStorage::patch(QString key, QString newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        StringItem *item = (StringItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
    }
    return ((StringItem *)KeyStorage::storageModel->get(key))->data;
}

double KeyStorage::patch(QString key, double newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        DoubleItem *item = (DoubleItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
    }
    return ((DoubleItem *)KeyStorage::storageModel->get(key))->data;
}

QVector<QString> KeyStorage::patch(QString key, QVector<QString> newValue)
{
    if (KeyStorage::storageModel->get(key)) {
        VectorStringItem *item = (VectorStringItem *)KeyStorage::storageModel->get(key);
        item->data = newValue;
    }
    return ((VectorStringItem *)KeyStorage::storageModel->get(key))->data;
}

void KeyStorage::remove(QString key)
{
    KeyStorage::storageModel->remove(key);
}
