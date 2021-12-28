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

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void deleteHistory(HistoryItem *item);
    void viewItem(HistoryItem *item);

private slots:
    void on_pushButton_clicked();

private:
    Ui::HistoryWidget *ui;
    HistoryItem *item;
    int relation;
};

#endif // HISTORYWIDGET_H
