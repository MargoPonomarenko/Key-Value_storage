#ifndef KEYSTORAGEMODEL_H
#define KEYSTORAGEMODEL_H
#include <QMap>
#include <QDate>

enum class DataType{
    qString, doubleValue, qStringVector
};

struct StorageItem:public QObject{
    Q_OBJECT
public:
    DataType itemType;
    QDate created;
    StorageItem(){};
    StorageItem(DataType type, QDate date){
        itemType = type;
        created = date;
    }
    StorageItem(const StorageItem& item){

        itemType = item.itemType;
        created = item.created;
    }
    StorageItem& operator=(const StorageItem& item) {
        if (this != &item) {
            itemType = item.itemType;
            created = item.created;
        }
        return *this;
    }
    friend QDataStream& operator<<(QDataStream& stream, const StorageItem& item) {
            stream << item.itemType << item.created;
            return stream;
    }
    friend QDataStream& operator>>(QDataStream& stream, StorageItem& item) {
            stream >> item.itemType >> item.created;
            return stream;
     }

};

struct StringItem: public StorageItem{
    QString data;
    StringItem(){};
    StringItem(DataType type, QDate date, QString data):StorageItem(type, date){
        this->data = data;
    }
    friend QDataStream& operator<<(QDataStream& stream, const StringItem& item) {
            stream << item.itemType << item.data;
            return stream;
    }
    friend QDataStream& operator>>(QDataStream& stream, StringItem& item) {
            stream >> item.itemType >> item.data;
            return stream;
     }
};

struct DoubleItem: public StorageItem{
    double data;
    DoubleItem(DataType type, QDate date, double data):StorageItem(type, date){
        this->data = data;
    }
};

struct VectorStringItem: public StorageItem{
    QVector<QString> data;
    VectorStringItem(DataType type, QDate date, QVector<QString> data):StorageItem(type, date){
        this->data = data;
    }
};

class KeyStorageModel
{
public:
    KeyStorageModel();
    virtual ~KeyStorageModel();

    void put(QString key, StorageItem *value);
    StorageItem *get(QString key);
    void patch(QString key, StorageItem *newValue);
    void remove(QString key);

private:
    //set life time func
    int timeLife = 1;
    void setTimeLife(int days);

    QMap<QString, StorageItem *> &storage;
    void removeOld();
};

#endif // KEYSTORAGEMODEL_H
