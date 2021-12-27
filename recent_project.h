#ifndef RECENT_PROJECT_H
#define RECENT_PROJECT_H

#include <QDialog>

#include <Models/projectdata.h>
#include <Models/recent_project_data.h>

namespace Ui {
class RecentProject;
}

class RecentProject : public QDialog
{
    Q_OBJECT

public:
    explicit RecentProject(QWidget *parent = nullptr);
    ~RecentProject();

signals:
    void loadProject(ProjectData *projData);

private slots:
    void on_openProj_clicked();
    void createProjectCallback(ProjectData *projData);

    void on_newProj_clicked();

private:
    QList<RecentProjectData* > *loadRecentPrjects();
    void saveRecentProjects();
    Ui::RecentProject *ui;
    QList<RecentProjectData* > *recents;
    QString recentDataFile;

};

#endif // RECENT_PROJECT_H
