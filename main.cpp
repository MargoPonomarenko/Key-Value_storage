#include "QDebug"
#include "keystorage.h"

int main()
{
    KeyStorage storage;
    storage.put("test", "Hello world!");
    qDebug() <<"Output data: " << storage.getString("test");
    qDebug() <<"Created in: " << KeyStorage::storageModel->get("test")->created;
    storage.patch("test", "Testing line");
    qDebug() <<"Output data: " << storage.getString("test");
    storage.remove("test");
    qDebug() <<"Updated data: " << storage.getString("test");
    return 0;
}
