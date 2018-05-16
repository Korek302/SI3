#ifndef NODE_H
#define NODE_H

#include <QVector>

class Node
{
public:
    Node(int** currBoard, int dim);
    Node(int** currBoard, int givenValue, int dim);
    Node(int** currBoard, int** prevBoard, int dim);
    Node(int** currBoard, int** prevBoard, int givenValue, int dim);

    bool isTerminal();
    int getValue();
    void setValue();
    int** getCurrBoard();
    QVector<Node> getChildren();

private:
    int** _prevBoard;
    int** _currBoard;
    QVector<Node> _children;
    int _value;

    void calcChildren();
    void calcValue();
};

#endif // NODE_H
