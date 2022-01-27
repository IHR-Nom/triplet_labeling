#ifndef MWMENUBAR_H
#define MWMENUBAR_H

#include <QMainWindow>
#include <QMenuBar>
#include <Qt>
#include <QToolBar>

#include <Models/projectdata.h>

class QAction;
class QMenu;
class QToolBar;

class MWMenubar : public QMainWindow
{
    Q_OBJECT

public:
    MWMenubar(QMainWindow *inMainWindow); // Constructor
    QAction *aSelectSame;
    QAction *aSelectDiff;
    QAction *aSelectQuest;
    QAction *aSelectNext;
    ~MWMenubar();                         // Destructor

private:
    QMainWindow  *mainWindow;

private slots:
    // Declare function prototypes
    void aFileNewCallback();
    void aFileOpenCallback();
    void aFileExitCallback();
    void createProjectCallback(ProjectData *projData);

signals:
    void createProject(ProjectData *projData);

private:
    // Declare function prototypes for creating actions and menus
    void createActions();
    void createMenus();

    // Define menubar elements
    QMenu *mFile;
    QMenu *mSelection;

    // Define toolbar elements
    QToolBar *tFile;

    // Define menubar and toolbar actions
    QAction *aFileNew;
    QAction *aFileOpen;
    QAction *aFileExit;
};

#endif // MWMENUBAR_H
