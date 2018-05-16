#ifndef GAMEWINDOWPVE_H
#define GAMEWINDOWPVE_H

#include <QMainWindow>
#include <limits>

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
    explicit GameWindowPvE(QWidget *parent, int dim);
    ~GameWindowPvE();

private:
    Ui::GameWindowPvE *ui;
    int _dim;
    int** _board;
    int** _prevBoard;
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;
    int _depth;

    void updateBoard(int posX, int posY, int val);
    void updateScore();
    QVector<int> getDiag1(int rowId, int colId);
    QVector<int> getDiag2(int rowId, int colId);
    int checkTab(QVector<int> row);
    void computerTurn();
    QPair<int, int> minimaxCoords();
    Node minimax(Node currNode, int depth, bool maximizingPlayer);
    QPair<int, int> diffSpots(int** tab1, int** tab2);
    //tree generateGameTree(int** currBoard);

private slots:
    void onPushButtonClick();
    int updateScore(int posX, int posY);
};

#endif // GAMEWINDOWPVE_H
