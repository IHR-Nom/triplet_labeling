#include "create_proj.h"
#include "recent_project.h"
#include "ui_recent_project.h"
#include <QJsonDocument>
#include <QStandardPaths>

RecentProject::RecentProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecentProject)
{
    ui->setupUi(this);
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    recentDataFile = QDir::cleanPath(dataDir + QDir::separator() + "recents.json");
}

RecentProject::~RecentProject()
{
    delete ui;
}

void RecentProject::on_openProj_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Project file"),
                                                "/home", tr("XML Files (*.triplet)"));
    if (!file.isEmpty()) {
        ProjectData *projData = new ProjectData(file);
        emit loadProject(projData);
        this->close();
    }
}

void RecentProject::createProjectCallback(ProjectData *projData)
{    
    emit loadProject(projData);
    this->close();
}

void RecentProject::on_newProj_clicked()
{
    CreateProj * createProjDialog = new CreateProj(this);
    connect(createProjDialog, &CreateProj::createProject, this, &RecentProject::createProjectCallback);
    createProjDialog->exec();
}

QList<RecentProjectData *> *RecentProject::loadRecentPrjects()
{
    QFile *recentProjFile = new QFile(recentDataFile);
    QList<RecentProjectData *> *recentProjects = new QList<RecentProjectData *>();
    if (!recentProjFile->exists()) {
        delete recentProjFile;
        return recentProjects;
    }
    recentProjFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = recentProjFile->readAll();
    recentProjFile->close();
    QJsonDocument d = QJsonDocument::fromJson(content.toUtf8());
    foreach (const QJsonValue & v, d.array()) {
            qDebug() << v.toObject().value("ID").toInt();
    }
    return recentProjects;
}

