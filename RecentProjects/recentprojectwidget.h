#ifndef RECENTPROJECTWIDGET_H
#define RECENTPROJECTWIDGET_H

#include <QWidget>

#include <Models/recent_project_data.h>

namespace Ui {
class RecentProjectWidget;
}

class RecentProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecentProjectWidget(QWidget *parent = nullptr, RecentProjectData *recentProjData = nullptr);
    ~RecentProjectWidget();

signals:
    void deleteProject(RecentProjectData *recentProjData);
    void openProject(RecentProjectData *recentProjData);

private slots:
    void on_remove_clicked();

    void on_openThisProj_clicked();

private:
    Ui::RecentProjectWidget *ui;
    RecentProjectData *recentProjData;
};

#endif // RECENTPROJECTWIDGET_H
