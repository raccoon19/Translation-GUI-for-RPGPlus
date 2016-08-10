#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabview.h"

#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->tabWidget->addTab(new tabView(), QIcon(QString("")), QString("Test"));
}

void MainWindow::on_actionSave_triggered()
{
    auto* tab = (tabView*)ui->tabWidget->widget(ui->tabWidget->currentIndex());

    util::mapTreeToYaml(tab->ui->treeWidget);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
