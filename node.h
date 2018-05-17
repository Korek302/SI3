#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QPair>

class Node
{
public:
    Node();
    Node(int** currBoard, QPair<int, int> move, int dim, int depth);
    ~Node();

    bool isTerminal();
    int getValue();
    QPair<int, int> getMove();
    bool getIsTerminal();
    int** getCurrBoard();
    QVector<Node> getChildren();

private:
    int** _currBoard;
    QPair<int, int> _move;
    QVector<Node> _children;
    int _value;
    int _dim;
    bool _isTerminal;
    int _depth;

    QVector<int> getDiag1(int rowId, int colId);
    QVector<int> getDiag2(int rowId, int colId);
    int checkTab(QVector<int> row);
    int** copyBoard(int** original);
    int calcValue();
    void calcChildren();
    void showBoard(int** original);
};

#endif // NODE_H
