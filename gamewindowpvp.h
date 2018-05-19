#ifndef GAMEWINDOWPVP_H
#define GAMEWINDOWPVP_H

#include "gamewindow.h"

#include <QPushButton>
#include <QGridLayout>


namespace Ui
{
    class GameWindowPvP;
}

class GameWindowPvP : public GameWindow
{
    Q_OBJECT

public:
    explicit GameWindowPvP(QWidget *parent);
    explicit GameWindowPvP(QWidget *parent, int dim);
    ~GameWindowPvP();

private:
    Ui::GameWindowPvP *ui;

    void initBoard();

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWPVP_H
