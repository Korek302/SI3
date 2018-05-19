#include "node.h"


Node::Node()
{
    _dim = 0;
    _value = 0;
    _isTerminal = false;
    _depth = 0;
    _move.first = 0;
    _move.second = 0;
    _utility = Utility();
}

Node::Node(int** currBoard, QPair<int, int> move, int dim, int depth)
{
    _dim = dim;
    _depth = depth;
    _utility = Utility();
    _currBoard = _utility.copyBoard(currBoard, _dim);
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
    /*
    for(int i = 0; i < _dim; i++)
    {
        delete _currBoard[i];
    }
    delete _currBoard;
    */
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
    out += _utility.checkTab(_utility.getDiag1(posX, posY, _currBoard, _dim));
    out += _utility.checkTab(_utility.getDiag2(posX, posY, _currBoard, _dim));
    return out;
}

void Node::calcChildren()
{
    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            if(_currBoard[i][j] == 0)
            {
                _currBoard[i][j] = 1;
                //int** tempCopy = _utility.copyBoard(_currBoard, _dim);
                _children.append(Node(_currBoard, QPair<int, int>(i, j), _dim, _depth - 1));
                _currBoard[i][j] = 0;
            }
        }
    }
}



