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
    auto * db = FamlDb::Instance();
    auto lst = db->GetPostCats();
    db->StoreLog(QString("Starting Faml application"));

    ui->setupUi(this);
    ui->postCats->addItem("");

    for(int i = 0; i < lst.count(); i++) {
        auto item = lst[i];
        postCatsData metadata(item.id, item.isActive);
        ui->postCats->addItem(item.name, QVariant::fromValue(metadata));
    }

    ui->postCatActive->setChecked(true);

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
            ui->postCats->setCurrentIndex(ui->postCats->count() - 1);
        }
    } else {        
        auto currentItem = ui->postCats->itemData(ui->postCats->currentIndex()).value<postCatsData>();
        res = db->StorePostCat(currentItem.first, ui->postCats->currentText(), ui->postCatActive->isChecked());

        if(!res) {
            msg.setText("Feil under lagring av kategori");
            return;
        } else {
            ui->postCats->setCurrentText(ui->postCatName->text());
        }
    }

    ui->postCatActive->setChecked(true);
    ui->postCatName->setText("");
    nameDirty = false;
}

void SettingsWindow::on_newPostButton_clicked()
{
    nameDirty = false;
    ui->postCats->setCurrentIndex(0);
    ui->postCatName->setText("");
    ui->postCatActive->setCheckState(Qt::Checked);
    ui->postCatName->setFocus();
}

void SettingsWindow::on_postCats_currentIndexChanged(int index)
{
    if(index == 0) return;

    nameDirty = true;
    auto d = ui->postCats->itemData(index).value<postCatsData>();

    ui->postCatName->setText(ui->postCats->currentText());
    ui->postCatActive->setChecked(d.second);
}
