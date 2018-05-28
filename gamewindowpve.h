#ifndef GAMEWINDOWPVE_H
#define GAMEWINDOWPVE_H

#include "gamewindow.h"
#include "node.h"

#include <limits>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <cstdlib>


namespace Ui
{
    class GameWindowPvE;
}

class GameWindowPvE : public GameWindow
{
    Q_OBJECT

public:
    explicit GameWindowPvE(QWidget *parent);
    explicit GameWindowPvE(QWidget *parent, int dim, bool aiStart, int depth, bool alfabeta, int gameMode, int nodeTraversal);
    ~GameWindowPvE();

private:
    Ui::GameWindowPvE *ui;
    int _depth;
    int _gameMode;
    int _nodeTraversal;
    bool _alfabeta;

    void computerTurn(QPair<int, int> move);
    void computerTurnRandom();
    Node minimax(Node currNode, int depth, bool maximizingPlayer);
    Node alfabeta(Node currNode, int depth, int alfa, int beta, bool maximizingPlayer);
    Node minimaxRandChildPick(Node currNode, int depth, bool maximizingPlayer);
    Node alfabetaRandChildPick(Node currNode, int depth, int alfa, int beta, bool maximizingPlayer);
    void initBoard();

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWPVE_H
