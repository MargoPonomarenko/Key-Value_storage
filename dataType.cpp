#include "dataType.h"

QDataStream& operator<<(QDataStream& os, const DataType& value)
{
    switch (value)
    {
        case DataType::qString:
            os << "qString";
            break;
        case DataType::doubleValue:
            os << "doubleValue";
            break;
        case DataType::qStringVector:
            os << "qStringVector";
            break;
    }

    return os;
}

QDataStream& operator>>(QDataStream& os, DataType& value)
{
    QString strValue;
    os >> strValue;

        if (strValue == "qString")
            value = DataType::qString;
        else if (strValue == "doubleValue")
            value = DataType::doubleValue;
        else if (strValue == "qStringVector")
            value = DataType::qStringVector;

    return os;
}
