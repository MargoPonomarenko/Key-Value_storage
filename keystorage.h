#ifndef KEYSTORAGE_H
#define KEYSTORAGE_H

#include "KeyValueStorage_global.h"
#include "sqlitebackupservice.h"
#include <QObject>

class KEYVALUESTORAGE_EXPORT KeyStorage: public QObject
{
    Q_OBJECT
public:
    KeyStorage();

    void put(QString key, QString value);
    void put(QString key, double value);
    void put(QString key, QVector<QString> value);

    void getString(QString key);
    void getDouble(QString key);
    void getStringVector(QString key);

    bool patch(QString key, QString newValue);
    bool patch(QString key, double newValue);
    bool patch(QString key, QVector<QString> newValue);

    void remove(QString key);


signals:
    void gettedString(QString value);
    void gettedDouble(double value);
    void gettedVectorString(QVector<QString> value);
    void loadFromDatabase(QString key);
    void saveToDatabase(QString key, StorageItem *value);

private slots:
    void onDataLoaded(QString key, StorageItem *value);

private:
    KeyStorageModel * storageModel;
    SQLiteBackupService *backupService;
    void put(QString key, StorageItem *value);
};

#endif // KEYSTORAGE_H
