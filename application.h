#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <mwmenubar.h>

#include <RecentProjects/recent_project.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    void showRecentProjects();
    void loadFirstCategory(QString symbol, QString tm, int nImages);
    void loadSecondCategory(QString symbol, QString tm, int nImages);
    ~Application();

private slots:
    void loadProject(ProjectData *projectData);

    void on_letters_select_currentTextChanged(const QString &arg1);

    void on_first_tm_currentTextChanged(const QString &arg1);

    void on_second_tm_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Application *ui;
    RecentProject *recent;
    ProjectData * projectData;
    MWMenubar *mwMenubar;
};
#endif // APPLICATION_H
