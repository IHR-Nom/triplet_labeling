#include "application.h"
#include "ui_application.h"


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);
    this->mwMenubar = new MWMenubar(this);
    connect(this->mwMenubar, &MWMenubar::createProject, this, &Application::loadProject);
}

void Application::loadProject(ProjectData *projectData)
{
    this->projectData = projectData;
    this->projectData->loadData();
    qDebug() << "Called";
}

Application::~Application()
{
    delete ui;
}
