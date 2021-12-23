#ifndef PROJECTDATA_H
#define PROJECTDATA_H
#include "QMap"
#include <QString>



class ProjectData
{
public:
    ProjectData();
    void loadData();
    void saveData();

    QString *getProjectName() const;

    QString *getDatasetDir() const;

    QMap<QString, QList<QString> > *getCategores() const;

    QList<QString> *getHistories() const;

    QMap<QString, int> *getRelationship() const;

private:
    QString *dataFileLocation;
    QString *projectName;
    QString *datasetDir;
    QMap<QString, QList<QString>> *categores;
    QList<QString> * histories;
    QMap<QString, int> *relationship;
};

#endif // PROJECTDATA_H
