#include "create_proj.h"

CreateProj::CreateProj(QWidget *parent): QDialog(parent), ui(new Ui::ProjectCreation)
{
    ui->setupUi(this);
}

void CreateProj::on_project_location_button_clicked()
{
    QString projectFile = QFileDialog::getSaveFileName(this, "Save file", "", ".triplet");
    if (!projectFile.isEmpty()) {
        if (!projectFile.contains(".triplet")) {
            projectFile = projectFile + ".triplet";
        }
        this->ui->project_location_edit->setText(projectFile);
    }
    qDebug() << projectFile;
}


void CreateProj::on_dataset_dir_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        this->ui->dataset_dir_edit->setText(dir);
    }
}

void CreateProj::on_buttonBox_accepted()
{
    QString proj_name = this->ui->project_name->text();
    QString proj_dir = this->ui->project_location_edit->text();
    QString dataset_dir = this->ui->dataset_dir_edit->text();

    ProjectData *projData = new ProjectData(proj_dir, proj_name, dataset_dir);
    projData->saveData();
    emit createProject(projData);
}

