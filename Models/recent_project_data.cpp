#include "recent_project_data.h"


RecentProjectData::RecentProjectData(QString projectName, QString projectLocation)
{
    this->projectName = projectName;
    this->projectLocation = projectLocation;
}

const QString &RecentProjectData::getProjectName() const
{
    return projectName;
}

const QString &RecentProjectData::getProjectLocation() const
{
    return projectLocation;
}
