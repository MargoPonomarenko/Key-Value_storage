#include "sqlitebackupservice.h"
#include "keystorage.h"

#include <QIODevice>

SQLiteBackupService::SQLiteBackupService()
{
    connectToDatabase();
    connect(storage, &KeyStorage::loadFromDatabase, this, &SQLiteBackupService::loadFromDatabase);
    connect(storage, &KeyStorage::saveToDatabase, this, &SQLiteBackupService::saveToDatabase);
}

void SQLiteBackupService::setStorage(KeyStorage *storage)
{
    this->storage = storage;
}

void SQLiteBackupService::saveToDatabase(QString key, StorageItem *value)
{
    if (!db->open()) {
        return;
    }

    QVariant data;
    data.setValue( *value);

    QByteArray serializedData; //серилізація об'єкту StorageItem
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
//    stream << *value;
    stream << data;

    QSqlQuery query;
    query.prepare("INSERT INTO storage (key, value) VALUES (?, ?)");
    query.addBindValue(key);
    query.addBindValue(serializedData);
    query.exec();
    db->close();
}

void SQLiteBackupService::loadFromDatabase(QString key)
{
    if (!db->open()) {
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM storage WHERE key='" + key + "'");
    query.exec();

    if(query.next()){
        QString key = query.value(0).toString();
        QVariant value = query.value(1);
        QObject *valueObject = qvariant_cast<QObject *>(value);
        StorageItem *item = qobject_cast<StorageItem *>(valueObject);
        emit dataLoaded(key, item);
    }
    db->close();
}

void SQLiteBackupService::connectToDatabase()
{
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("storage.db");
}
