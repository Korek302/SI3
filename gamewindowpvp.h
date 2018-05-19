#ifndef GAMEWINDOWPVP_H
#define GAMEWINDOWPVP_H

#include "utility.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QVector>
#include <string.h>


namespace Ui
{
    class GameWindowPvP;
}

class GameWindowPvP : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindowPvP(QWidget *parent);
    explicit GameWindowPvP(QWidget *parent, int dim);
    ~GameWindowPvP();

private:
    Ui::GameWindowPvP *ui;
    int _dim;
    int** _board;
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;
    Utility _utility;

    int updateScore(int posX, int posY);
    void initBoard();

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWPVP_H
