#ifndef GAMEWINDOWPVE_H
#define GAMEWINDOWPVE_H

#include <QMainWindow>
#include <limits>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QVector>
#include <string.h>

#include "node.h"


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

    void updateBoard(int posX, int posY, int val);
    QVector<int> getDiag1(int rowId, int colId);
    QVector<int> getDiag2(int rowId, int colId);
    int checkTab(QVector<int> row);
    void computerTurn(QPair<int, int> move);
    Node minimax(Node currNode, int depth, bool maximizingPlayer);
    QPair<int, int> diffSpots(int** tab1, int** tab2);
    int** copyBoard(int** original);
    int updateScore(int posX, int posY);
    void showBoard(int** original);

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWPVE_H
