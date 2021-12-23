#include "menu.h"

Menu::Menu(Application * app, Ui::Application * ui)
{
    this->application = app;
    this->ui = ui;

    QMenu *file_menu = ui->menubar->addMenu(tr("&File"));
    auto *new_proj = new QAction("&New Project...", this);
    file_menu->addAction(new_proj);
    auto *add_proj = new QAction("&Open Project...", this);
    file_menu->addAction(add_proj);
    auto *quit = new QAction("&Quit", this);
    file_menu->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}
