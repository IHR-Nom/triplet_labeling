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
    void addHistoryWidget(HistoryItem *item);
    void fillCategories();
    ~Application();

private slots:
    void loadProject(ProjectData *projectData);
    void deleteHistoryItem(HistoryItem *item);

    void on_letters_select_currentTextChanged(const QString &arg1);

    void on_first_tm_currentTextChanged(const QString &arg1);

    void on_second_tm_currentTextChanged(const QString &arg1);

    void on_shuffle_clicked();

    void on_next_clicked();

    void on_clear_clicked();

    void on_zoomIn_clicked();

    void on_zoomOut_clicked();

private:
    void saveRelationship(QString symbol, QString first_tm, QString second_tm, int relationship);
    Ui::Application *ui;
    RecentProject *recent;
    ProjectData * projectData = nullptr;
    MWMenubar *mwMenubar;
};
#endif // APPLICATION_H
