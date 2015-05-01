#include "logwindow.h"
#include "ui_logwindow.h"
#include "famldb.h"

LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);

    auto * db = FamlDb::Instance();
    auto logs = db->GetLogs();
    ui->logList->addItems(logs);
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::on_closeButton_clicked()
{
    this->close();
}

void LogWindow::on_clearButton_clicked()
{
    auto * db = FamlDb::Instance();
    db->ClearLogs();
    ui->logList->clear();
}
