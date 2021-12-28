#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

#include <Models/historyitem.h>

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget *parent, HistoryItem *item, int relation);
    ~HistoryWidget();

private:
    Ui::HistoryWidget *ui;
};

#endif // HISTORYWIDGET_H
