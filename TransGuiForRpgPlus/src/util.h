#ifndef UTIL_H
#define UTIL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFile>

#include <yaml-cpp/yaml.h>

class util
{

public:
    explicit util();

    static QString mapTreeToYaml(QTreeWidget* tree);
    static void getAllChilds(QTreeWidgetItem* topLevel, YAML::Emitter& out, bool fromTopLevel);

    static void saveFile(QString filename, QString yaml);
signals:

public slots:

private:

};

#endif // UTIL_H
