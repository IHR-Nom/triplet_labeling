#include "projectdata.h"

#include <QDirIterator>


ProjectData::ProjectData(QString dataFileLocation, QString projectName, QString datasetDir)
{
    this->dataFileLocation = &dataFileLocation;
    this->projectName = &projectName;
    this->datasetDir = &datasetDir;
}

void ProjectData::loadData()
{
    QDirIterator it(*this->datasetDir, QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    categories = new QMap<QString, QList<QString> *>();
    symbolCategoriesMap = new QMap<QString, QList<QString> *>();
    while (it.hasNext()) {
        QFileInfo * file = new QFileInfo(it.next());
        QString category = file->baseName().split("_").at(1);
        QString symbol = file->baseName().split("_").at(0);
        if (!categories->contains(category)) {
            categories->insert(category, new QList<QString>());
        }
        this->categories->value(category)->append(file->absoluteFilePath());
        if (!symbolCategoriesMap->contains(symbol)) {
            symbolCategoriesMap->insert(symbol, new QList<QString>());
        }
        symbolCategoriesMap->value(symbol)->append(category);
    }
}

QString *ProjectData::getProjectName() const
{
    return projectName;
}

QString *ProjectData::getDatasetDir() const
{
    return datasetDir;
}

QMap<QString, QList<QString> *> *ProjectData::getCategores() const
{
    return categories;
}

QList<HistoryItem> *ProjectData::getHistories() const
{
    return histories;
}

QMap<QString, int> *ProjectData::getRelationship() const
{
    return relationship;
}
