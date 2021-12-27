#include "application.h"
#include "ui_application.h"
#include <QImageReader>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDir>
#include <QCollator>


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);    
    recent = new RecentProject(this);
    connect(recent, &RecentProject::loadProject, this, &Application::loadProject);
    this->mwMenubar = new MWMenubar(this);
    connect(this->mwMenubar, &MWMenubar::createProject, this, &Application::loadProject);
}

void Application::showRecentProjects()
{
    this->recent->show();
}

void Application::loadFirstCategory(QString symbol, QString tm, int nImages)
{
    QList<QString> *images = projectData->getSymbolCategoriesMap()->value(symbol)->value(tm);
    QString imgPath = images->at(QRandomGenerator::global()->bounded(0, images->size()));
    QImageReader reader(imgPath);
    reader.setAutoTransform(true);
    const QImage image = reader.read();

    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(imgPath), reader.errorString()));
        return;
    }
    ui->image->setPixmap(QPixmap::fromImage(image));
}

void Application::loadSecondCategory(QString symbol, QString tm, int nImages)
{
    QList<QString> *images = projectData->getSymbolCategoriesMap()->value(symbol)->value(tm);
    QString imgPath = images->at(QRandomGenerator::global()->bounded(0, images->size()));
    QImageReader reader(imgPath);
    reader.setAutoTransform(true);
    const QImage image = reader.read();

    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(imgPath), reader.errorString()));
        return;
    }
    ui->image_2->setPixmap(QPixmap::fromImage(image));
}


void Application::loadProject(ProjectData *projData)
{
    projectData = projData;
    projectData->loadData();
    for (QString category : projData->getSymbolCategoriesMap()->keys()) {
        this->ui->letters_select->addItem(category);
    }
    this->show();
}

Application::~Application()
{
    delete ui;
}

void Application::on_letters_select_currentTextChanged(const QString &symbol)
{
    QList<QString> tms = projectData->getSymbolCategoriesMap()->value(symbol)->keys();
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(tms.begin(), tms.end(), [&](const QString& s1, const QString& s2){ return coll.compare(s1, s2) < 0; });

    this->ui->first_tm->clear();
    this->ui->second_tm->clear();
    for (int i = 0; i < tms.size(); i++) {
        this->ui->first_tm->addItem(tms.at(i));
        this->ui->second_tm->addItem(tms.at(i));
    }
}


void Application::on_first_tm_currentTextChanged(const QString &tm)
{
    if (tm != "") {
        QString symbol = this->ui->letters_select->currentText();
        loadFirstCategory(symbol, tm, 1);
    }
}


void Application::on_second_tm_currentTextChanged(const QString &tm)
{
    if (tm != "") {
        QString symbol = this->ui->letters_select->currentText();
        loadSecondCategory(symbol, tm, 1);
    }
}


void Application::on_pushButton_2_clicked()
{
    QString symbol = this->ui->letters_select->currentText();
    QString tm1 = this->ui->first_tm->currentText();
    loadFirstCategory(symbol, tm1, 1);
    QString tm2 = this->ui->second_tm->currentText();
    loadSecondCategory(symbol, tm2, 1);
}

