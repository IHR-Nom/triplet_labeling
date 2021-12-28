#include "create_proj.h"
#include "recent_project.h"
#include "recentprojectwidget.h"
#include "ui_recent_project.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>

RecentProject::RecentProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecentProject)
{
    ui->setupUi(this);
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    recentDataFile = QDir::cleanPath(dataDir + QDir::separator() + "recents.json");
    QString parentPath = QFileInfo(recentDataFile).dir().absolutePath();
    QDir dir(parentPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    recents = loadRecentPrjects();
    for (int i = 0; i < recents->count(); i++) {
        RecentProjectWidget *recentProjWidget = new RecentProjectWidget(this, recents->at(i));
        ui->recentArea->layout()->addWidget(recentProjWidget);
        connect(recentProjWidget, &RecentProjectWidget::deleteProject, this, &RecentProject::deleteRecentCallback);
        connect(recentProjWidget, &RecentProjectWidget::openProject, this, &RecentProject::openProjCallback);
    }
    ui->recentArea->layout()->setAlignment(Qt::AlignTop);
}

RecentProject::~RecentProject()
{
    delete ui;
    delete recents;
}

void RecentProject::on_openProj_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Project file"),
                                                "/home", tr("XML Files (*.triplet)"));
    if (!file.isEmpty()) {
        ProjectData *projData = new ProjectData(file);
        emit loadProject(projData);
        this->accept();
    }
}

void RecentProject::createProjectCallback(ProjectData *projData)
{    
    RecentProjectData *recentProjData = new RecentProjectData(projData->getProjectName(), projData->getDataFileLocation());
    recents->insert(0, recentProjData);
    saveRecentProjects();
    emit loadProject(projData);
    this->accept();
}

void RecentProject::deleteRecentCallback(RecentProjectData *recent)
{
    int index = recents->indexOf(recent);
    recents->removeAt(index);
    QLayoutItem *item = ui->recentArea->layout()->takeAt(index);
    QWidget *widget = item->widget();
    ui->recentArea->layout()->removeWidget(widget);
    delete widget;
    delete item;
    saveRecentProjects();
}

void RecentProject::openProjCallback(RecentProjectData *recent)
{
    ProjectData *projData = new ProjectData(recent->getProjectLocation());
    emit loadProject(projData);
    this->accept();
}

void RecentProject::on_newProj_clicked()
{
    CreateProj * createProjDialog = new CreateProj(this);
    connect(createProjDialog, &CreateProj::createProject, this, &RecentProject::createProjectCallback);
    createProjDialog->exec();
}

QList<RecentProjectData *> *RecentProject::loadRecentPrjects()
{
    QFile recentProjFile(recentDataFile);
    QList<RecentProjectData *> *recentProjects = new QList<RecentProjectData *>();
    if (!recentProjFile.exists()) {
        return recentProjects;
    }
    recentProjFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = recentProjFile.readAll();
    recentProjFile.close();
    QJsonDocument doc(QJsonDocument::fromJson(content.toUtf8()));
    foreach (const QJsonValue & v, doc.array()) {
        QJsonObject objValue = v.toObject();
        RecentProjectData *recentProjData = new RecentProjectData(objValue.value("name").toString(), objValue.value("location").toString());
        recentProjects->append(recentProjData);
    }
    return recentProjects;
}

void RecentProject::saveRecentProjects()
{
    QFile recentProjFile(recentDataFile);
    if(!recentProjFile.open(QIODevice::ReadWrite)) {
          qDebug() << "File open error";
    } else {
          qDebug() <<"JSONTest2 File open!";
    }
    recentProjFile.resize(0);

    QJsonArray jsonArray;
    for (int i = 0; i < recents->count(); ++i) {
        QJsonObject jsonObject;
        jsonObject.insert("name", recents->at(i)->getProjectName());
        jsonObject.insert("location", recents->at(i)->getProjectLocation());
        jsonArray.append(jsonObject);
    }
    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray);
    recentProjFile.write(jsonDoc.toJson());
    recentProjFile.close();
}


void RecentProject::on_RecentProject_rejected()
{
    QCoreApplication::quit();
}

