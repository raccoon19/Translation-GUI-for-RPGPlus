#include "tabview.h"

tabView::tabView(QWidget *parent, QTreeWidget* widget) :
    QWidget(parent),
    ui(new Ui::tabView)
{
    ui->setupUi(this);
    if(widget){
        ui->treeWidget = widget;
    }
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
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, "Key");
    item->setText(1, "Translation");
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    ui->treeWidget->addTopLevelItem(item);
}

void tabView::RemoveItem(){
    delete ui->treeWidget->currentItem();
}

void tabView::AddChild(){
    //can't add child if toplevel doesnt exist
    if(ui->treeWidget->currentItem() == NULL){
        return;
    }

    ui->treeWidget->currentItem()->setText(1, "");

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget->currentItem());

    item->setText(0, "K");
    item->setText(1, "V");
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void tabView::onTreeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column){
    ui->treeWidget->editItem(item, column);
}

