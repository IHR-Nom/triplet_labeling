#include "listutils.h"

#include <QCollator>

ListUtils::ListUtils()
{

}

void ListUtils::sort(QList<QString> *list)
{
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(list->begin(), list->end(), [&](const QString& s1, const QString& s2){ return coll.compare(s1, s2) < 0; });
}
