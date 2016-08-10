#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    //get filename
    QString filename = QFileDialog::getSaveFileName(this, tr("New file"),
                                                    "",
                                                    tr("YAML (*.yml)"));
    ui->tabWidget->addTab(new tabView(), QIcon(QString("")), filename);
}

void MainWindow::on_actionSave_triggered()
{
    auto* tab = (tabView*)ui->tabWidget->widget(ui->tabWidget->currentIndex());

    QString yaml = util::mapTreeToYaml(tab->ui->treeWidget);

    QString filename = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    util::saveFile(filename, yaml);

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "",
                                                    tr("YAML (*.yml)"));
    tabView* view = new tabView();

    YAML::Node node = util::readYamlFile(filename);
    util::mapYamlToTree(node, view);
    ui->tabWidget->addTab(view, QIcon(QString("")), filename);
}
