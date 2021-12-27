#ifndef RECENTPROJECTDATA_H
#define RECENTPROJECTDATA_H

#include <QString>



class RecentProjectData
{
public:
    RecentProjectData(QString projectName, QString projectLocation);
    const QString &getProjectName() const;

    const QString &getProjectLocation() const;

private:
    QString projectName;
    QString projectLocation;
};

#endif // RECENTPROJECTDATA_H
