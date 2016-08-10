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
                                                    tr("YAML (*.yaml)"));
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
