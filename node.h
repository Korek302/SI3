#ifndef NODE_H
#define NODE_H

#include "utility.h"

#include <QVector>
#include <QPair>

class Node
{
public:
    Node();
    Node(int** currBoard, QPair<int, int> move, int dim, int depth);
    Node(const Node& other);
    ~Node();

    int getValue();
    QPair<int, int> getMove();
    bool getIsTerminal();
    int** getCurrBoard();
    QVector<Node> getChildren();

    void operator=(const Node& other);

private:
    int** _currBoard;
    QPair<int, int> _move;
    QVector<Node> _children;
    int _value;
    int _dim;
    bool _isTerminal;
    int _depth;
    Utility _utility;

    bool isTerminal();
    int calcValue();
    int calcValueColsure();
    void calcChildren();
};

#endif // NODE_H
