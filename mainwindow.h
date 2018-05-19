#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindowpvp.h"
#include "gamewindowpve.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameWindowPvP *gameWindowPvP;
    GameWindowPvE *gameWindowPvE;

private slots:
    void onPushButtonClick();
    void onPushButton_2Click();
};

#endif // MAINWINDOW_H
