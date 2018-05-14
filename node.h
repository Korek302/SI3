#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    Node(int** currBoard);
    Node(int** currBoard, int givenValue);
    Node(int** currBoard, int** prevBoard);
    Node(int** currBoard, int** prevBoard, int givenValue);

    void isTerminal();
    int getValue();
    void setValue();
    int** getCurrBoard();
    QVector<Node> getChildren();

private:
    int** _prevBoard;
    int** _currBoard;
    QVector<Node> _children;
    int value;

    void calcChildren();
    void calcValue();
};

#endif // NODE_H
