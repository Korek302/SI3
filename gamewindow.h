#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "utility.h"

#include <QMainWindow>
#include <QDebug>
#include <QVector>


class GameWindow : public QMainWindow
{
public:
    explicit GameWindow(QWidget *parent);
    explicit GameWindow(QWidget *parent, int dim);
    ~GameWindow();

protected:
    int _dim;
    int** _board;
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;
    Utility _utility;

    int updateScore(int posX, int posY);
    virtual void initBoard();
};

#endif // GAMEWINDOW_H
