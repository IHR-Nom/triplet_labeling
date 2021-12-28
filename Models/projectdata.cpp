#include "projectdata.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QDirIterator>


ProjectData::ProjectData(QString dataFileLocation, QString projectName, QString datasetDir)
{
    this->dataFileLocation = dataFileLocation;
    this->relationships = new QMap<QString, QMap<QString, int> *>();
    this->histories = new QList<HistoryItem *> ();
    this->projectName = projectName;
    this->datasetDir = datasetDir;
    symbolCategoriesMap = new QMap<QString, QMap<QString, QList<QString> *> *>();
}

ProjectData::ProjectData(QString dataFileLocation)
{
    this->dataFileLocation = dataFileLocation;
    this->relationships = new QMap<QString, QMap<QString, int> *>();
    this->histories = new QList<HistoryItem *> ();
    symbolCategoriesMap = new QMap<QString, QMap<QString, QList<QString> *> *>();
}

ProjectData::~ProjectData()
{
    delete symbolCategoriesMap;
    delete histories;
    delete relationships;
}

void ProjectData::loadData()
{
    QFile projFile(dataFileLocation);
    projFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = projFile.readAll();
    projFile.close();
    QJsonDocument doc(QJsonDocument::fromJson(content.toUtf8()));
    QJsonObject jsonObject = doc.object();
    datasetDir = jsonObject.value("dataset_dir").toString();
    projectName = jsonObject.value("name").toString();

    for(auto r : jsonObject.value("relations").toArray()) {
        QMap<QString, int> *current = new QMap<QString, int>();
        QJsonObject relation = r.toObject();
        for (auto r2 : relation.value("relations").toArray()) {
            QJsonObject tmp = r2.toObject();
            current->insert(tmp.value("category").toString(), tmp.value("relationship").toInt());
        }
        relationships->insert(relation.value("category").toString(), current);
    }

    for (auto h : jsonObject.value("histories").toArray()) {
        QJsonObject hisObj = h.toObject();
        HistoryItem *historyItem = new HistoryItem(
                    hisObj.value("category").toString(),
                    hisObj.value("secondary_category").toString(),
                    hisObj.value("timestamp").toString().toLong());
        histories->append(historyItem);
    }


    QDirIterator it(this->datasetDir, QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo * file = new QFileInfo(it.next());
        QString category = file->baseName().split("_").at(1);
        QString symbol = file->baseName().split("_").at(0);
        if (!symbolCategoriesMap->contains(symbol)) {
            symbolCategoriesMap->insert(symbol, new QMap<QString, QList<QString> *>());
        }
        if (!symbolCategoriesMap->value(symbol)->contains(category)) {
            symbolCategoriesMap->value(symbol)->insert(category, new QList<QString>());
        }
        symbolCategoriesMap->value(symbol)->value(category)->append(file->absoluteFilePath());
    }
}

void ProjectData::saveData()
{
    QFile projFile(dataFileLocation);
    if(!projFile.open(QIODevice::ReadWrite)) {
          qDebug() << "File open error";
    } else {
          qDebug() <<"JSONTest2 File open!";
    }
    projFile.resize(0);
    QJsonObject jsonObject;
    jsonObject.insert("data_file_location", dataFileLocation);
    jsonObject.insert("name", projectName);
    jsonObject.insert("dataset_dir", datasetDir);
    QJsonArray relations;
    for(auto r : relationships->keys()) {
        QMap<QString, int> *current = relationships->value(r);
        QJsonArray current_relations;
        for (auto r2 : current->keys()) {
            QJsonObject tmp;
            tmp.insert("category", r2);
            tmp.insert("relationship", current->value(r2));
            current_relations.append(tmp);
        }
        QJsonObject relation;
        relation.insert("category", r);
        relation.insert("relations", current_relations);
        relations.append(relation);
    }
    jsonObject.insert("relations", relations);

    QJsonArray historyItems;
    for (int i = 0; i < histories->count(); i++) {
        QJsonObject historyItem;
        historyItem.insert("category", histories->at(i)->getCategory());
        historyItem.insert("secondary_category", histories->at(i)->getSecondCategory());
        historyItem.insert("timestamp", QString::number(histories->at(i)->getTimestamp()));
        historyItems.append(historyItem);
    }
    jsonObject.insert("histories", historyItems);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);
    projFile.write(jsonDoc.toJson());
    projFile.close();

}

void ProjectData::addRelationship(QString firstCategory, QString secondCategory, int relation)
{
    if (!relationships->contains(firstCategory)) {
        QMap<QString, int> *relationship = new QMap<QString, int>();
        relationship->insert(secondCategory, relation);
        relationships->insert(firstCategory, relationship);
    }

    if (!relationships->value(firstCategory)->contains(secondCategory)) {
        relationships->value(firstCategory)->insert(secondCategory, relation);
    }
}

void ProjectData::deleteRelationship(QString firstCategory, QString secondCategory)
{
    if (relationships->contains(firstCategory)) {
        if (relationships->value(firstCategory)->contains(secondCategory)) {
            relationships->value(firstCategory)->remove(secondCategory);
        }
    }
}

void ProjectData::addHistory(HistoryItem *item)
{
    histories->append(item);
}

void ProjectData::deleteHistory(HistoryItem *item)
{
    histories->removeOne(item);
}

QString ProjectData::getProjectName() const
{
    return projectName;
}

QString ProjectData::getDatasetDir() const
{
    return datasetDir;
}


QList<HistoryItem *> *ProjectData::getHistories() const
{
    return histories;
}

QMap<QString, QMap<QString, int> *> *ProjectData::getRelationships() const
{
    return relationships;
}

QString ProjectData::getDataFileLocation() const
{
    return dataFileLocation;
}

QMap<QString, QMap<QString, QList<QString> *> *> *ProjectData::getSymbolCategoriesMap() const
{
    return symbolCategoriesMap;
}
