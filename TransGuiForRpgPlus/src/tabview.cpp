#include "tabview.h"

tabView::tabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabView)
{
    ui->setupUi(this);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(QStringList() << "Key" << "Translation");

    connect(ui->treeWidget ,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onTreeWidgetItemDoubleClicked(QTreeWidgetItem*, int)), Qt::QueuedConnection );
}

tabView::~tabView()
{
    delete ui;
}

void tabView::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu;
    contextMenu.addAction("AddItem", this, SLOT(AddItem()));
    contextMenu.addAction("AddChild", this, SLOT(AddChild()));
    contextMenu.addAction("Delete", this, SLOT(RemoveItem()));

    contextMenu.exec(ui->treeWidget->mapToGlobal(pos));
}

void tabView::AddItem(){
    QTreeWidgetItem* test = new QTreeWidgetItem(ui->treeWidget);
    test->setText(0, "Key");
    test->setText(1, "Translation");
    test->setFlags(test->flags() | Qt::ItemIsEditable);

    ui->treeWidget->addTopLevelItem(test);
}

void tabView::RemoveItem(){
    delete ui->treeWidget->currentItem();
    qDebug() << "Item deleted.";
}

void tabView::AddChild(){
    //can't add child if toplevel doesnt exist
    if(ui->treeWidget->currentItem() == NULL){
        return;
    }

    QTreeWidgetItem* test = new QTreeWidgetItem(ui->treeWidget->currentItem());

    test->setText(0, "");
    test->setText(1, "");
    test->setFlags(test->flags() | Qt::ItemIsEditable);
}

void tabView::onTreeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column){
    ui->treeWidget->editItem(item, column);
}

