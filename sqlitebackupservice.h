#ifndef SQLITEBACKUPSERVICE_H
#define SQLITEBACKUPSERVICE_H
#include "keyStorageModel.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QObject>

class KeyStorage;

class SQLiteBackupService: public QObject
{
    Q_OBJECT
public:
    SQLiteBackupService();
    void setStorage(KeyStorage *storage);
    void initSlotConnection();

public slots:
    void saveToDatabase(QString key, StorageItem *value);
    void loadFromDatabase(QString key);

signals:
    void dataLoaded(QString key, StorageItem *value);

private:
    KeyStorage *storage;
    QSqlDatabase db;
    void connectToDatabase();


};

#endif // SQLITEBACKUPSERVICE_H
