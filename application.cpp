#include "application.h"
#include "ui_application.h"
#include <QImageReader>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDir>
#include <QCollator>
#include <Utils/listutils.h>
#include <History/historywidget.h>


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);    
    recent = new RecentProject(this);
    connect(recent, &RecentProject::loadProject, this, &Application::loadProject);
    this->mwMenubar = new MWMenubar(this);
    connect(this->mwMenubar, &MWMenubar::createProject, this, &Application::loadProject);    
    ui->historyScrollWidget->setLayout(new QVBoxLayout(this));
    ui->historyScrollWidget->layout()->setContentsMargins(5, 2, 5, 2);
    ui->historyScrollWidget->layout()->setSpacing(2);
    ui->historyScrollWidget->layout()->setAlignment(Qt::AlignTop);
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
    for (int i = 0; i < projectData->getHistories()->size(); i++) {
        HistoryItem *item = projectData->getHistories()->at(i);
        int relation = projectData->getRelationships()->value(item->getCategory())->value(item->getSecondCategory());
        HistoryWidget *w = new HistoryWidget(this, item, relation);
        ui->historyScrollWidget->layout()->addWidget(w);
    }
    QList<QString> categories = projData->getSymbolCategoriesMap()->keys();
    ListUtils::sort(&categories);
    for (int i = 0; i < categories.size(); i++) {
        this->ui->letters_select->addItem(categories.at(i));
    }
    this->show();
}

Application::~Application()
{
    delete ui;
    delete projectData;
    delete recent;
    delete mwMenubar;
}

void Application::on_letters_select_currentTextChanged(const QString &symbol)
{
    QList<QString> tms = projectData->getSymbolCategoriesMap()->value(symbol)->keys();
    ListUtils::sort(&tms);

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


void Application::on_shuffle_clicked()
{
    QString symbol = this->ui->letters_select->currentText();
    QString tm1 = this->ui->first_tm->currentText();
    loadFirstCategory(symbol, tm1, 1);
    QString tm2 = this->ui->second_tm->currentText();
    loadSecondCategory(symbol, tm2, 1);
}


void Application::on_next_clicked()
{
    int state = 0;
    if (ui->sameAuthor->isChecked()) {
        state = 1;
    } else if (ui->cbSameAuthor->isChecked()) {
        state = 2;
    } else if (ui->cbDiffAuthor->isChecked()) {
        state = 3;
    } else if (ui->diffAuthor->isChecked()) {
        state = 4;
    }
    QString symbol = this->ui->letters_select->currentText();
    QString tm1 = this->ui->first_tm->currentText();
    QString tm2 = this->ui->second_tm->currentText();
    saveRelationship(symbol, tm1, tm2, state);
    emit on_clear_clicked();
}

void Application::saveRelationship(QString symbol, QString first_tm, QString second_tm, int relationship)
{
    if (relationship == 0) {
        return;
    }
    HistoryItem *item = new HistoryItem(first_tm, second_tm);
    HistoryWidget *w = new HistoryWidget(this, item, relationship);
    ui->historyScrollWidget->layout()->addWidget(w);
    projectData->addRelationship(first_tm, second_tm, relationship);
    projectData->addHistory(item);
    projectData->saveData();
}


void Application::on_clear_clicked()
{
    ui->sameAuthor->setAutoExclusive(false);
    ui->cbSameAuthor->setAutoExclusive(false);
    ui->cbDiffAuthor->setAutoExclusive(false);
    ui->diffAuthor->setAutoExclusive(false);

    ui->sameAuthor->setChecked(false);
    ui->cbSameAuthor->setChecked(false);
    ui->cbDiffAuthor->setChecked(false);
    ui->diffAuthor->setChecked(false);

    ui->sameAuthor->setAutoExclusive(true);
    ui->cbSameAuthor->setAutoExclusive(true);
    ui->cbDiffAuthor->setAutoExclusive(true);
    ui->diffAuthor->setAutoExclusive(true);
}

