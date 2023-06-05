#include "sqlitebackupservice.h"
#include "keystorage.h"

#include <QIODevice>
#include <QDebug>

SQLiteBackupService::SQLiteBackupService():db{QSqlDatabase::addDatabase("QSQLITE")}
{
    connectToDatabase();

}

void SQLiteBackupService::setStorage(KeyStorage *storage)
{
    this->storage = storage;
}

void SQLiteBackupService::saveToDatabase(QString key, StorageItem *value)
{
    qDebug()<<"Gettign signal saveToDatabase";
    if (!db.open()) {
        qDebug()<<"Error of connecting to db";
        return;
    }

    QVariant data;
    data.setValue( *value);

    QByteArray serializedData; //серилізація об'єкту StorageItem
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
//    stream << *value;
    stream << data;
    qDebug()<< "saveToDatabase result: "<< data;

    QSqlQuery query;
    query.prepare("INSERT INTO storage (key, value) VALUES (?, ?)");
    query.addBindValue(key);
    query.addBindValue(serializedData);
    query.exec();
    db.close();
}

void SQLiteBackupService::loadFromDatabase(QString key)
{
    if (!db.open()) {
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM storage WHERE key='" + key + "'");
    query.exec();

    if(query.next()){
        QString key = query.value(0).toString();
        QVariant value = query.value(1);
        //QObject *valueObject = qvariant_cast<QObject *>(value);

        QByteArray serializedData = qvariant_cast<QByteArray>(value);
        StorageItem data;
        //StorageItem item;
        QDataStream stream(&serializedData, QIODevice::ReadOnly);
        stream >> data;

        //StorageItem *item = qobject_cast<StorageItem *>(valueObject);
        qDebug()<< "loadFromDatabase result: "<<&data;
        //qDebug()<< "loadFromDatabase result: "<<&item;
        emit dataLoaded(key, &data);
        //emit dataLoaded(key, item);
    }
    db.close();
}

void SQLiteBackupService::connectToDatabase()
{
    db.setDatabaseName("./storage.db");
    QSqlQuery query;
    if (!db.open()) {
        return;
    }
    query.exec("CREATE TABLE IF NOT EXISTS storage (key TEXT PRIMARY KEY, value BLOB)");
    if (!query.isValid()) {
        //qDebug() << "Error creating table: " << query.lastError().text();
        db.close();
     }

}

void SQLiteBackupService::initSlotConnection()
{
    connect(storage, &KeyStorage::loadFromDatabase, this, &SQLiteBackupService::loadFromDatabase);
    connect(storage, &KeyStorage::saveToDatabase, this, &SQLiteBackupService::saveToDatabase);
}


