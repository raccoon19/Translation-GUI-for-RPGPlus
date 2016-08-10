#ifndef TABVIEW_H
#define TABVIEW_H

#include <QWidget>
#include <QMenu>
#include <QTreeWidgetItem>
#include <QDebug>

#include "ui_tabview.h"
#include "util.h"

#include <yaml-cpp/yaml.h>

namespace Ui {
class tabView;
}

class tabView : public QWidget
{
    Q_OBJECT

public:
    explicit tabView(QWidget *parent = 0);
    ~tabView();

    Ui::tabView *ui;

private slots:

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void AddItem();
    void AddChild();
    void RemoveItem();

    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column);

private:


};

#endif // TABVIEW_H
