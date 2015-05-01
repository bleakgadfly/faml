#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "famldb.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    auto * db = FamlDb::Instance();
    db->StoreLog(QString("Starting Faml application"));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete logWindow;
    delete settingsWindow;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    logWindow = new LogWindow();
    logWindow->show();
}

void MainWindow::on_settingsButton_clicked()
{
    settingsWindow = new SettingsWindow();
    settingsWindow->show();
}
