#include "create_proj.h"
#include "mwmenubar.h"
#include <QDebug>

MWMenubar::MWMenubar(QMainWindow *parent)
{
    mainWindow = parent;

    createActions(); // Create all individual menu actions
    createMenus();   // Create main window menubar
}

MWMenubar::~MWMenubar()
{
    // The destructor should not be needed, as the menubar is part of the
    // main window and will be deleted when the main window is closed.
}

// Create individual menu action callbacks
void MWMenubar::aFileNewCallback()
{
    CreateProj * createProjDialog = new CreateProj(mainWindow);
    if (createProjDialog->exec()) {
        QString data_path = createProjDialog->getDataPath();
    }
    qDebug() << "Pressing File->New!";
}

void MWMenubar::aFileOpenCallback()
{
    qDebug() << "Pressing File->Open!";
}

void MWMenubar::aFileExitCallback()
{
    qDebug() << "Pressing File->Exit!";
    mainWindow->close();
}

// Function for creating all menu actions
void MWMenubar::createActions()
{
//    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
//    aFileNew = new QAction(newIcon, tr("&New..."), this);
    aFileNew = new QAction(tr("&New project..."), this);
    aFileNew->setShortcuts(QKeySequence::New);
    aFileNew->setStatusTip(tr("Create a new file"));
    connect(aFileNew, &QAction::triggered, this, &MWMenubar::aFileNewCallback);

//    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
//    aFileOpen = new QAction(openIcon, tr("&Open..."), this);
    aFileOpen = new QAction(tr("&Open project..."), this);
    aFileOpen->setShortcuts(QKeySequence::Open);
    aFileOpen->setStatusTip(tr("Open an existing file"));
    connect(aFileOpen, &QAction::triggered, this, &MWMenubar::aFileOpenCallback);

    aFileExit = new QAction(tr("E&xit"), this);
    aFileExit->setShortcuts(QKeySequence::Quit);
    aFileExit->setStatusTip(tr("Exit the application"));
    connect(aFileExit, &QAction::triggered, this, &MWMenubar::aFileExitCallback);
}

void MWMenubar::createMenus()
{
    mFile = mainWindow->menuBar()->addMenu(tr("&File"));
    mFile->addAction(aFileNew);
    mFile->addAction(aFileOpen);
    mFile->addSeparator();
    mFile->addAction(aFileExit);
}
