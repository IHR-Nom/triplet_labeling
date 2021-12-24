#include "historyitem.h"
#include <qdatetime.h>


HistoryItem::HistoryItem(QString *category)
{
    this->category = category;
    this->timestamp = QDateTime::currentSecsSinceEpoch();
}
