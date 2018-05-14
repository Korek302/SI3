#ifndef GAMEWINDOWPVE_H
#define GAMEWINDOWPVE_H

#include <QMainWindow>

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
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;

    void updateBoard(int posX, int posY, int val);
    void updateScore();
    QVector<int> getDiag1(int rowId, int colId);
    QVector<int> getDiag2(int rowId, int colId);
    int checkTab(QVector<int> row);
    //tree generateGameTree(int** currBoard);

private slots:
    void onPushButtonClick();
    int updateScore(int posX, int posY);
};

#endif // GAMEWINDOWPVE_H
