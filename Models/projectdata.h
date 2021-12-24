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
    void loadData();
    void saveData();

    QString *getProjectName() const;

    QString *getDatasetDir() const;

    QMap<QString, QList<QString> *> *getCategores() const;

    QList<HistoryItem> *getHistories() const;

    QMap<QString, int> *getRelationship() const;

private:
    QString *dataFileLocation;
    QString *projectName;
    QString *datasetDir;
    QMap<QString, QList<QString> *> *categories;
    QMap<QString, QList<QString> *> *symbolCategoriesMap;
    QList<HistoryItem> * histories;
    QMap<QString, int> *relationship;
};

#endif // PROJECTDATA_H
