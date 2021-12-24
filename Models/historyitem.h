#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QString>



class HistoryItem
{
public:
    HistoryItem(QString *category);

private:
    QString * category;
    QMap<QString, QList<QString> *> * samples;
    long timestamp;
};

#endif // HISTORYITEM_H
