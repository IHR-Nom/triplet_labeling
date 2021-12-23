#ifndef CREATE_PROJ_H
#define CREATE_PROJ_H

#include "ui_create_proj.h"
#include <QDialog>
#include <QFileDialog>


class CreateProj : public QDialog, public Ui::ProjectCreation
{
    Q_OBJECT

public:
    explicit CreateProj(QWidget *parent = nullptr);
    QString getDataPath();

private slots:
    void on_project_location_button_clicked();

    void on_dataset_dir_button_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ProjectCreation *ui;
    QString data_path;
};

#endif // CREATE_PROJ_H
