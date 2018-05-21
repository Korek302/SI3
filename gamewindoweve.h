#ifndef GAMEWINDOWEVE_H
#define GAMEWINDOWEVE_H

#include "gamewindow.h"
#include "node.h"

#include <limits>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>


namespace Ui
{
    class GameWindowEvE;
}

class GameWindowEvE : public GameWindow
{
    Q_OBJECT

public:
    explicit GameWindowEvE(QWidget *parent);
    explicit GameWindowEvE(QWidget *parent, int dim, bool aiStart, int depth, bool alfabeta);
    ~GameWindowEvE();

private:
    Ui::GameWindowEvE *ui;
    int _depth;
    bool _alfabeta;
    bool _red;

    void computerTurn(QPair<int, int> move);
    Node minimax(Node currNode, int depth, bool maximizingPlayer);
    Node alfabeta(Node currNode, int depth, int alfa, int beta, bool maximizingPlayer);
    void initBoard();

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOWEVE_H
