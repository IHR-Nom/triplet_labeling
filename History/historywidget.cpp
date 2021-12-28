#include "historywidget.h"
#include "ui_historywidget.h"

#include <QIcon>

HistoryWidget::HistoryWidget(QWidget *parent, HistoryItem* item, int relation) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    int h = 16;
    this->relation = relation;
    this->item = item;
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
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    installEventFilter(this);
}

bool HistoryWidget::eventFilter(QObject *object, QEvent *event)
{

    if (event->type() == QEvent::MouseButtonPress ) {
        qDebug() << "Pressed";
    }

    return QObject::eventFilter(object, event);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::on_pushButton_clicked()
{
    emit deleteHistory(item);
}

