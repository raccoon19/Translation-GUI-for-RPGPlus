#include "util.h"

util::util()
{

}

QString util::mapTreeToYaml(QTreeWidget* tree){
    YAML::Emitter out;

    out << YAML::BeginMap;
    //get all toplevel elements
    for( int i = 0; i < tree->topLevelItemCount(); ++i ) {
       QTreeWidgetItem* topLevelItem = tree->topLevelItem(i);
       out << YAML::Key << topLevelItem->text(0).toStdString().c_str();
       if(topLevelItem->text(1) == ""){
           getAllChilds(topLevelItem, out, true);
       }
       else{
           out << YAML::Value << topLevelItem->text(1).toStdString().c_str();
       }

    }
    out << YAML::EndMap;

    return out.c_str();
}

void util::getAllChilds(QTreeWidgetItem* topLevel, YAML::Emitter& out, bool fromTopLevel){

    out << YAML::BeginMap;

    for( int i = 0; i < topLevel->childCount(); ++i ){
        out << YAML::Key << topLevel->child(i)->text(0).toStdString().c_str();

        if(topLevel->child(i)->childCount() == 0){
            out << YAML::Value << topLevel->child(i)->text(1).toStdString().c_str();
        }
        else {
            getAllChilds( topLevel->child(i) , out , false);
        }
    }
    out << YAML::EndMap;
}

void util::saveFile(QString filename, QString yaml){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out << yaml;
    file.close();
}

YAML::Node util::readYamlFile(QString filename){

    std::ifstream fin(filename.toStdString().c_str());
    YAML::Node tree = YAML::Load(fin);

    if(!tree.IsMap()){
        qDebug() << "Only Map is supported. May crash.";
    }

    return tree;
}

void util::mapYamlToTree(YAML::Node node, tabView* view){
    QTreeWidget* tree = view->ui->treeWidget;

    try {
        for(YAML::const_iterator it=node.begin();it!=node.end();++it){
            QString key = QString::fromStdString(it->first.as<std::string>());
            QString value("");
            QTreeWidgetItem* item = addToplevelItem(tree, key, value);
            if(it->second.size() > 0){
                getAllYamlChilds(it->second, item);
            }
            else {
                value = QString::fromStdString(it->second.as<std::string>());
                modifyTreeWidgetItem(item, key, value);
            }
        }
    } catch(YAML::ParserException& e) {
        qDebug() << QString::fromStdString(e.what());
    }
}

void util::getAllYamlChilds(YAML::Node node, QTreeWidgetItem* topLevel){

    for(YAML::const_iterator it=node.begin();it!=node.end();++it){
        QString key = QString::fromStdString(it->first.as<std::string>());
        QString value("");
        QTreeWidgetItem* child = addChildItem(topLevel, key, value);
        if(it->second.size() > 0){
            getAllYamlChilds(it->second, child);
        }
        else {
            value = QString::fromStdString(it->second.as<std::string>());
            modifyTreeWidgetItem(child, key, value);
        }
    }
}

QTreeWidgetItem* util::addToplevelItem(QTreeWidget* treeWidget, QString first, QString second){
    QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
    item->setText(0, first);
    item->setText(1, second);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    treeWidget->addTopLevelItem(item);
    return item;
}

void util::modifyTreeWidgetItem(QTreeWidgetItem* item, QString first, QString second){
    item->setText(0, first);
    item->setText(1, second);
}

QTreeWidgetItem* util::addChildItem(QTreeWidgetItem* item, QString first, QString second){
    QTreeWidgetItem* add = new QTreeWidgetItem(item);

    add->setText(0, first);
    add->setText(1, second);
    add->setFlags(add->flags() | Qt::ItemIsEditable);

    return add;
}

