#ifndef GAMEWINDOWPVE_H
#define GAMEWINDOWPVE_H

#include "node.h"
#include "utility.h"

#include <QMainWindow>
#include <limits>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QVector>
#include <string.h>


namespace Ui
{
    class GameWindowPvE;
}

class GameWindowPvE : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindowPvE(QWidget *parent);
    explicit GameWindowPvE(QWidget *parent, int dim, bool aiStart);
    ~GameWindowPvE();

private:
    Ui::GameWindowPvE *ui;
    int _dim;
    int** _board;
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;
    int _depth;
    Utility _utility;

    void computerTurn(QPair<int, int> move);
    Node minimax(Node currNode, int depth, bool maximizingPlayer);
    int updateScore(int posX, int posY);
    void initBoard();

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWPVE_H
