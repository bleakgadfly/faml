#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

private slots:
    void on_saveButton_clicked();

    void on_newPostButton_clicked();

    void on_postCats_currentIndexChanged(int index);

private:
    Ui::SettingsWindow *ui;
    bool nameDirty = false;
};

#endif // SETTINGSWINDOW_H
