#ifndef UTIL_H
#define UTIL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFile>

#include <fstream>
#include <string>

#include "tabview.h"
#include "ui_mainwindow.h"

#include <yaml-cpp/yaml.h>

class util
{

public:
    explicit util();

    static QString mapTreeToYaml(QTreeWidget* tree);
    static void getAllChilds(QTreeWidgetItem* topLevel, YAML::Emitter& out, bool fromTopLevel);

    static void saveFile(QString filename, QString yaml);

    static YAML::Node readYamlFile(QString filename);
    static void mapYamlToTree(YAML::Node node, tabView* view);
    static void getAllYamlChilds(YAML::Node node, QTreeWidgetItem* topLevel);
    static QTreeWidgetItem* addToplevelItem(QTreeWidget* treeWidget, QString first, QString second);
    static void modifyTreeWidgetItem(QTreeWidgetItem* item, QString first, QString second);
    static QTreeWidgetItem* addChildItem(QTreeWidgetItem* item, QString first, QString second);
signals:

public slots:

private:

};

#endif // UTIL_H
