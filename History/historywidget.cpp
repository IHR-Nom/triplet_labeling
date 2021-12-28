#include "historywidget.h"
#include "ui_historywidget.h"

#include <QIcon>

HistoryWidget::HistoryWidget(QWidget *parent, HistoryItem* item, int relation) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    int h = 16;
    if (relation == 1) {
        ui->icon->setPixmap(QIcon(":/Icons/Icons/checked.png").pixmap(h, h));
    } else if (relation == 2) {
        ui->icon->setPixmap(QIcon(":/Icons/Icons/question_green.svg").pixmap(h, h));
    } else if (relation == 3) {
        ui->icon->setPixmap(QIcon(":/Icons/Icons/red_icon.svg").pixmap(h, h));
    } else if (relation == 4) {
        ui->icon->setPixmap(QIcon(":/Icons/Icons/No_icon_red.svg").pixmap(h, h));
    }
    ui->label->setText("TM " + item->getCategory() + " and TM " + item->getSecondCategory());
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}
