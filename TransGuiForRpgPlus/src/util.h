#ifndef UTIL_H
#define UTIL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>

#include <yaml-cpp/yaml.h>

class util
{

public:
    explicit util();

    static QString mapTreeToYaml(QTreeWidget* tree);
    static void getAllChilds(QTreeWidgetItem* topLevel, YAML::Emitter& out, bool fromTopLevel);

signals:

public slots:

private:

};

#endif // UTIL_H
