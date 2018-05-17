#include "node.h"


Node::Node()
{
    _dim = 0;
    _value = 0;
    _isTerminal = false;
    _depth = 0;
    _move.first = 0;
    _move.second = 0;
}

Node::Node(int** currBoard, QPair<int, int> move, int dim, int depth)
{
    _dim = dim;
    _depth = depth;
    _currBoard = copyBoard(currBoard);
    _isTerminal = isTerminal();
    _move.first = move.first;
    _move.second = move.second;
    _value = calcValue();

    if(!_isTerminal && !(_depth < 1))
    {
        calcChildren();
    }
}

Node::~Node()
{
    for(int i = 0; i < _dim; i++)
    {
        //delete _currBoard[i];
    }
    //delete _currBoard;
}

int Node::getValue()
{
    return _value;
}

bool Node::getIsTerminal()
{
    return _isTerminal;
}

QPair<int, int> Node::getMove()
{
    return _move;
}

int** Node::getCurrBoard()
{
    return _currBoard;
}

QVector<Node> Node::getChildren()
{
    return _children;
}

bool Node::isTerminal()
{
    int counter = 0;
    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            if(_currBoard[i][j] == 0)
            {
                counter++;
            }
        }
    }
    return counter < 1 ? true : false;
}

int Node::calcValue()
{
    int out = 0;
    int posX = _move.first;
    int posY = _move.second;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[posX][i] == 0)
        {
            break;
        }
        if(i == _dim - 1)
        {
            out += _dim;
        }
    }
    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[i][posY] == 0)
        {
            break;
        }
        if(i == _dim - 1)
        {
            out += _dim;
        }
    }
    out += checkTab(getDiag1(posX, posY));
    out += checkTab(getDiag2(posX, posY));
    return out;
}

QVector<int> Node::getDiag1(int rowId, int colId)
{
    QVector<int> out1;
    int tempI = rowId;
    int tempJ = colId;
    while (tempI >= 0 && tempJ >= 0)
    {
        out1.push_back(_currBoard[tempI][tempJ]);
        tempI--;
        tempJ--;
    }
    tempI = rowId + 1;
    tempJ = colId + 1;
    while (tempI < _dim && tempJ < _dim)
    {
        out1.push_back(_currBoard[tempI][tempJ]);
        tempI++;
        tempJ++;
    }
    return out1;
}

QVector<int> Node::getDiag2(int rowId, int colId)
{
    QVector<int> out1;
    int tempI = rowId - 1;
    int tempJ = colId + 1;
    while (tempI >= 0 && tempJ < _dim)
    {
        out1.push_back(_currBoard[tempI][tempJ]);
        tempI--;
        tempJ++;
    }
    tempI = rowId;
    tempJ = colId;
    while (tempI < _dim && tempJ >= 0)
    {
        out1.push_back(_currBoard[tempI][tempJ]);
        tempI++;
        tempJ--;
    }
    return out1;
}

int Node::checkTab(QVector<int> row)
{
    int i = 0;
    for (; i < row.length(); i++)
    {
        if(row.at(i) == 0)
        {
            return 0;
        }
    }
    return i > 2 ? i : 0;
}

int** Node::copyBoard(int** original)
{
    int** out = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        out[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            out[i][j] = original[i][j];
        }
    }
    return out;
}

void Node::calcChildren()
{
    //int** tempCopy = copyBoard(_currBoard);

    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            if(_currBoard[i][j] == 0)
            {
                _currBoard[i][j] = 1;
                int** tempCopy = copyBoard(_currBoard);
                _children.append(Node(tempCopy, QPair<int, int>(i, j), _dim, _depth - 1));
                _currBoard[i][j] = 0;
            }
        }
    }
}

void Node::showBoard(int** original)
{
    QString str = "";
    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            str += (QString::number(original[i][j]) + " ");
        }
        qDebug(str.toLatin1());
        str = "";
    }
    qDebug("\n");
}







