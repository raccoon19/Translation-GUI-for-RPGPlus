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
