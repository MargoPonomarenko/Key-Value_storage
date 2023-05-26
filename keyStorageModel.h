#ifndef KEYSTORAGEMODEL_H
#define KEYSTORAGEMODEL_H
#include "QMap"

enum class DataType{
    qString, doubleValue, qStringVector
};

struct StorageItem{
    DataType itemType;
};

struct StringItem: public StorageItem{
    QString data;
};

struct DoubleItem: public StorageItem{
    double data;
};

struct VectorStringItem: public StorageItem{
    QVector<QString> data;
};

class KeyStorageModel
{
public:
    KeyStorageModel();
    virtual ~KeyStorageModel();
    void put(QString key, StorageItem value);
private:
    QMap<QString, StorageItem> * storage;
};

#endif // KEYSTORAGEMODEL_H
