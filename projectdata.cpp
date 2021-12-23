#include "projectdata.h"

ProjectData::ProjectData()
{

}

QString *ProjectData::getProjectName() const
{
    return projectName;
}

QString *ProjectData::getDatasetDir() const
{
    return datasetDir;
}

QMap<QString, QList<QString> > *ProjectData::getCategores() const
{
    return categores;
}

QList<QString> *ProjectData::getHistories() const
{
    return histories;
}

QMap<QString, int> *ProjectData::getRelationship() const
{
    return relationship;
}
