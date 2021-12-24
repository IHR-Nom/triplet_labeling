#include "application.h"
#include "recent_project.h"
#include "ui_application.h"


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);    
    recent = new RecentProject(this);
    connect(recent, &RecentProject::loadProject, this, &Application::loadProject);
    this->mwMenubar = new MWMenubar(this);
    connect(this->mwMenubar, &MWMenubar::createProject, this, &Application::loadProject);
}

void Application::showRecentProjects()
{
    this->recent->show();
}

void Application::loadProject(ProjectData *projectData)
{
    this->projectData = projectData;
    this->projectData->loadData();
    this->show();
}

Application::~Application()
{
    delete ui;
}
