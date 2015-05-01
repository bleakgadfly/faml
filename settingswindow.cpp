#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "famldb.h"
#include <QMessageBox>

typedef QPair<int, bool> postCatsData;
Q_DECLARE_METATYPE(postCatsData)

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    ui->postCats->addItem("");
    ui->postCats->addItem("Cato", QVariant::fromValue(postCatsData(12, true)));
    ui->postCats->addItem("Lisa", QVariant::fromValue(postCatsData(12, false)));
    ui->postCats->addItem("Hus og hjem", QVariant::fromValue(postCatsData(12, true)));

    nameDirty = false;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_saveButton_clicked()
{
    QMessageBox msg;
    auto * db = FamlDb::Instance();
    auto postCatName = ui->postCatName->text();

    if(postCatName.isEmpty()) {
        msg.setText("Navn kan ikke være tomt når man lagrer");
        msg.show();

        return;
    }

    FAMLRESULT res;
    if(!nameDirty) {
        res = db->StoreNewPostCat(ui->postCatName->text());
        if(res == FAMLOK) {
            ui->postCats->addItem(ui->postCatName->text(), QVariant::fromValue(postCatsData(-1, true)));
        }
    } else {
        res = db->StorePostCat(0, ui->postCatName->text(), ui->postCatActive->isChecked());
        if(!res) {
            msg.setText("Feil under lagring av kategori");
        }
    }

    ui->postCatActive->setChecked(true);
    ui->postCatName->setText("");
}

void SettingsWindow::on_newPostButton_clicked()
{
    nameDirty = false;
    ui->postCats->setCurrentIndex(0);
    ui->postCatName->setText("");
    ui->postCatActive->setCheckState(Qt::Checked);
}

void SettingsWindow::on_postCats_currentIndexChanged(int index)
{
    nameDirty = true;
    postCatsData d = ui->postCats->itemData(index).value<postCatsData>();

    ui->postCatName->setText(ui->postCats->currentText());
    ui->postCatActive->setChecked(d.second);
}
