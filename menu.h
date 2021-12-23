#ifndef MENU_H
#define MENU_H

#include <application.h>

class Menu
{
public:
    Menu(Application *app, Ui::Application *ui);
    ~Menu();
private:
    Application *application;
    Ui::Application *ui;
};

#endif // MENU_H
