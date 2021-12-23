#include "application.h"
#include "ui_application.h"


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);
    this->mwMenubar = new MWMenubar(this);
}

Application::~Application()
{
    delete ui;
}

