#ifndef DATATYPE_H
#define DATATYPE_H
#include <QDataStream>
#include <QString>

enum class DataType{
    qString, doubleValue, qStringVector

};

QDataStream& operator<<(QDataStream& os, const DataType& value);
QDataStream& operator>>(QDataStream& os, DataType& value);

#endif // DATATYPE_H
