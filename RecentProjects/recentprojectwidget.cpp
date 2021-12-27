#include "recentprojectwidget.h"
#include "ui_recentprojectwidget.h"

RecentProjectWidget::RecentProjectWidget(QWidget *parent, RecentProjectData *recentProj) :
    QWidget(parent),
    ui(new Ui::RecentProjectWidget)
{
    ui->setupUi(this);
    recentProjData = recentProj;
    ui->projName->setText(recentProjData->getProjectName());
    ui->projPath->setText(recentProjData->getProjectLocation());
}

RecentProjectWidget::~RecentProjectWidget()
{
    delete ui;
}

void RecentProjectWidget::on_remove_clicked()
{
    emit deleteProject(recentProjData);
}


void RecentProjectWidget::on_openThisProj_clicked()
{
    emit openProject(recentProjData);
}

