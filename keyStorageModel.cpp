#include "keyStorageModel.h"

KeyStorageModel::KeyStorageModel()
{
    storage = new QMap<QString, StorageItem>;
}

KeyStorageModel::~KeyStorageModel()
{
    storage->clear();
    delete storage;
}

void KeyStorageModel::put(QString key, StorageItem value)
{
    (* storage)[key] = value;
}

