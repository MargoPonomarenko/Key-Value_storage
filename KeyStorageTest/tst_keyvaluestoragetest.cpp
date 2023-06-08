#include <QtTest>
#include <keystorage.h>
//#include <../../Key-Value_storage/keystorage.h>
//#include <../../Key-Value_storage/keyStorageModel.h>
//#include <../../Key-Value_storage/sqlitebackupservice.h>


// add necessary includes here

class KeyValueStorageTest : public QObject
{
    Q_OBJECT

public:
    KeyValueStorageTest();
    ~KeyValueStorageTest();

private:
    KeyStorage *storageTest;
    QString value;

private slots:
    void initTestCase();
    void getString(QString value);
    void testCheckGettedString();
};

KeyValueStorageTest::KeyValueStorageTest()
{}

KeyValueStorageTest::~KeyValueStorageTest()
{}

void KeyValueStorageTest::initTestCase()
{
    storageTest = new KeyStorage;
    connect(storageTest, &KeyStorage::gettedString, this, &KeyValueStorageTest::getString);
    storageTest->put("one", "Item 1");
    storageTest->getString("one");
    QTest::qWait(5000);
    qDebug()<<"Constructor";
}

void KeyValueStorageTest::getString(QString value)
{
    this->value = value;
    qDebug()<<"Into test func";
}

void KeyValueStorageTest::testCheckGettedString()
{
    qDebug()<<"Into test2";
    QCOMPARE(value, "Item 1");
}

QTEST_APPLESS_MAIN(KeyValueStorageTest)

#include "tst_keyvaluestoragetest.moc"
