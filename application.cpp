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

    ui->first_img_area->layout()->setAlignment(Qt::AlignCenter);
    ui->second_img_area->layout()->setAlignment(Qt::AlignCenter);
    ui->numb_images->setCurrentIndex(1);
}

void Application::showRecentProjects()
{
    this->recent->show();
}

void Application::loadFirstCategory(QString symbol, QString tm, int index)
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
    QLabel *imageArea = qobject_cast<QLabel*>(ui->first_img_area->layout()->itemAt(index)->widget());
    imageArea->setPixmap(QPixmap::fromImage(image));
}

void Application::loadSecondCategory(QString symbol, QString tm, int index)
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
    QLabel *imageArea = qobject_cast<QLabel*>(ui->second_img_area->layout()->itemAt(index)->widget());
    imageArea->setPixmap(QPixmap::fromImage(image));
}

void Application::addHistoryWidget(HistoryItem *item)
{
    int relation = projectData->getRelationships()->value(item->getCategory())->value(item->getSecondCategory());
    HistoryWidget *w = new HistoryWidget(this, item, relation);
    ui->historyScrollWidget->layout()->addWidget(w);
    connect(w, &HistoryWidget::deleteHistory, this, &Application::deleteHistoryItem);
}


void Application::loadProject(ProjectData *projData)
{
    projectData = projData;
    projectData->loadData();
    for (int i = 0; i < projectData->getHistories()->size(); i++) {
        HistoryItem *item = projectData->getHistories()->at(i);
        addHistoryWidget(item);
    }
    QList<QString> categories = projData->getSymbolCategoriesMap()->keys();
    ListUtils::sort(&categories);
    for (int i = 0; i < categories.size(); i++) {
        this->ui->letters_select->addItem(categories.at(i));
    }
    this->show();
}

void Application::deleteHistoryItem(HistoryItem *item)
{
    int itemIndex = projectData->getHistories()->indexOf(item);
    projectData->deleteRelationship(item->getCategory(), item->getSecondCategory());
    projectData->deleteRelationship(item->getSecondCategory(), item->getCategory());
    projectData->deleteHistory(item);
    QLayoutItem *layoutItem = ui->historyScrollWidget->layout()->takeAt(itemIndex);
    QWidget *widget = layoutItem->widget();
    ui->historyScrollWidget->layout()->removeWidget(widget);
    delete widget;
    delete item;
    delete layoutItem;
    projectData->saveData();
}

Application::~Application()
{
    delete ui;
    if (projectData != nullptr) {
        delete projectData;
    }
    delete recent;
    delete mwMenubar;
}

void Application::on_letters_select_currentTextChanged(const QString &symbol)
{
    QList<QString> tms = projectData->getSymbolCategoriesMap()->value(symbol)->keys();
    ListUtils::sort(&tms);

    this->ui->first_tm->clear();    
    for (int i = 0; i < tms.size(); i++) {
        this->ui->first_tm->addItem(tms.at(i));
    }
}


void Application::on_first_tm_currentTextChanged(const QString &tm)
{
    if (tm != "") {
        this->ui->second_tm->clear();
        QString symbol = this->ui->letters_select->currentText();
        QList<QString> tms = projectData->getSymbolCategoriesMap()->value(symbol)->keys();
        ListUtils::sort(&tms);
        for (int i = 0; i < tms.size(); i++) {
            if (projectData->getRelationships()->contains(tm) && projectData->getRelationships()->value(tm)->contains(tms.at(i))) {
                continue;
            }
            if (tms.at(i) == tm) {
                continue;
            }
            this->ui->second_tm->addItem(tms.at(i));
        }
        emit on_shuffle_clicked();
    }
}


void Application::on_second_tm_currentTextChanged(const QString &tm)
{
    if (tm != "") {
        emit on_shuffle_clicked();
    }
}


void Application::on_shuffle_clicked()
{
    QString symbol = this->ui->letters_select->currentText();
    QString tm1 = this->ui->first_tm->currentText();
    QString tm2 = this->ui->second_tm->currentText();
    if (symbol == "" || tm1 == "" || tm2 == "") {
        return;
    }
    int n_images = ui->numb_images->currentText().toInt();
    for (int i = 0; i < n_images; i++) {
        loadFirstCategory(symbol, tm1, i);
        loadSecondCategory(symbol, tm2, i);
    }
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
    emit on_first_tm_currentTextChanged(tm1);
}

void Application::saveRelationship(QString symbol, QString first_tm, QString second_tm, int relationship)
{
    if (relationship == 0) {
        return;
    }    
    projectData->addRelationship(first_tm, second_tm, relationship);
    projectData->addRelationship(second_tm, first_tm, relationship);
    HistoryItem *item = new HistoryItem(first_tm, second_tm);
    projectData->addHistory(item);
    projectData->saveData();
    addHistoryWidget(item);
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


void Application::on_zoomIn_clicked()
{    
    int n_images = ui->numb_images->currentText().toInt();
    for (int i = 0; i < n_images; i++) {
        QLabel *imageArea = qobject_cast<QLabel*>(ui->first_img_area->layout()->itemAt(i)->widget());
        QPixmap pic = imageArea->pixmap(Qt::ReturnByValue);
        imageArea->setPixmap(pic.scaled(1.5 * pic.size()));

        imageArea = qobject_cast<QLabel*>(ui->second_img_area->layout()->itemAt(i)->widget());
        pic = imageArea->pixmap(Qt::ReturnByValue);
        imageArea->setPixmap(pic.scaled(1.5 * pic.size()));
    }
}


void Application::on_zoomOut_clicked()
{
    int n_images = ui->numb_images->currentText().toInt();
    for (int i = 0; i < n_images; i++) {
        QLabel *imageArea = qobject_cast<QLabel*>(ui->first_img_area->layout()->itemAt(i)->widget());
        QPixmap pic = imageArea->pixmap(Qt::ReturnByValue);
        imageArea->setPixmap(pic.scaled(0.8 * pic.size()));

        imageArea = qobject_cast<QLabel*>(ui->second_img_area->layout()->itemAt(i)->widget());
        pic = imageArea->pixmap(Qt::ReturnByValue);
        imageArea->setPixmap(pic.scaled(0.8 * pic.size()));
    }
}


void Application::on_numb_images_currentTextChanged(const QString &numb_images)
{
    QLayoutItem * item = ui->first_img_area->layout()->takeAt(0);
    while (item != 0) {
        delete item->widget();
        delete item;
        item = ui->first_img_area->layout()->takeAt(0);
    }
    item = ui->second_img_area->layout()->takeAt(0);
    while (item != 0) {
        delete item->widget();
        delete item;
        item = ui->second_img_area->layout()->takeAt(0);
    }
    int n_images = numb_images.toInt();
    for (int i = 0; i < n_images; i++) {
        QLabel *first = new QLabel(this);
        first->setAlignment(Qt::AlignHCenter);
        ui->first_img_area->layout()->addWidget(first);
        QLabel *second = new QLabel(this);
        second->setAlignment(Qt::AlignHCenter);
        ui->second_img_area->layout()->addWidget(second);
    }
    emit on_shuffle_clicked();
}

