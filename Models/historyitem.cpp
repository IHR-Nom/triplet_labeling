#include "historyitem.h"
#include <qdatetime.h>


HistoryItem::HistoryItem(QString category, QString secondaryCategory)
{
    this->category = category;
    this->secondCategory = secondaryCategory;
    this->timestamp = QDateTime::currentSecsSinceEpoch();
}

HistoryItem::HistoryItem(QString category, QString secondaryCategory, long timestamp)
{
    this->category = category;
    this->secondCategory = secondaryCategory;
    this->timestamp = timestamp;
}

const QString HistoryItem::getCategory() const
{
    return category;
}

const QString HistoryItem::getSecondCategory() const
{
    return secondCategory;
}

long HistoryItem::getTimestamp() const
{
    return timestamp;
}
