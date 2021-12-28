#ifndef PROJECTDATA_H
#define PROJECTDATA_H
#include "QMap"
#include "historyitem.h"
#include <QString>


class ProjectData
{
public:
    ProjectData(QString dataFileLocation, QString projectName, QString datasetDir);
    ProjectData(QString dataFileLocation);
    ~ProjectData();
    void loadData();
    void saveData();
    void addRelationship(QString firstCategory, QString secondCategory, int relation);
    void deleteRelationship(QString firstCategory, QString secondCategory);
    void addHistory(HistoryItem *item);
    void deleteHistory(HistoryItem *item);
    QString getProjectName() const;

    QString getDatasetDir() const;

    QMap<QString, QList<QString> *> *getCategores() const;

    QList<HistoryItem *> *getHistories() const;

    QMap<QString, QMap<QString, int> *> *getRelationships() const;

    QString getDataFileLocation() const;

    QMap<QString, QMap<QString, QList<QString> *> *> *getSymbolCategoriesMap() const;

private:
    QString dataFileLocation;
    QString projectName;
    QString datasetDir;
    QMap<QString, QList<QString> *> *categories;
    QMap<QString, QMap<QString, QList<QString> *> *> *symbolCategoriesMap;
    QList<HistoryItem *> * histories;
    QMap<QString, QMap<QString, int> *> *relationships;
};

#endif // PROJECTDATA_H
