#ifndef CREATE_PROJ_H
#define CREATE_PROJ_H

#include "projectdata.h"
#include "ui_create_proj.h"
#include <QDialog>
#include <QFileDialog>


class CreateProj : public QDialog, public Ui::ProjectCreation
{
    Q_OBJECT

public:
    explicit CreateProj(QWidget *parent = nullptr);
    QString getDataPath();

    ProjectData *getProjData() const;

private slots:
    void on_project_location_button_clicked();

    void on_dataset_dir_button_clicked();

    void on_buttonBox_accepted();

signals:
    void createProject(ProjectData *projData);

private:
    Ui::ProjectCreation *ui;

};

#endif // CREATE_PROJ_H
