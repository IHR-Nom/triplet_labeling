#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QString>



class HistoryItem
{
public:
    HistoryItem(QString category, QString secondaryCategory);
    HistoryItem(QString category, QString secondaryCategory, long timestamp);

    const QString getCategory() const;

    const QString getSecondCategory() const;

    long getTimestamp() const;

private:
    QString category;
    QString secondCategory;
    long timestamp;
};

#endif // HISTORYITEM_H
