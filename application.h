#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <mwmenubar.h>
#include <projectdata.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private:
    Ui::Application *ui;
    ProjectData * projectData;
    MWMenubar *mwMenubar;
};
#endif // APPLICATION_H
