#ifndef APPLICATION_H
#define APPLICATION_H

#include "recent_project.h"

#include <QMainWindow>
#include <mwmenubar.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    void showRecentProjects();
    ~Application();

private slots:
    void loadProject(ProjectData *projectData);

private:
    Ui::Application *ui;
    RecentProject *recent;
    ProjectData * projectData;
    MWMenubar *mwMenubar;
};
#endif // APPLICATION_H
