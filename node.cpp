#include "node.h"


Node::Node() //: Node(NULL, QPair<int, int>(0, 0), 0, 0)
{
    _dim = 0;
    _value = 0;
    _isTerminal = false;
    _depth = 0;
    _move.first = 0;
    _move.second = 0;
    _currBoard = NULL;
    //_utility.initBoard(_currBoard, _dim);
}

Node::Node(int** currBoard, QPair<int, int> move, int dim, int depth, int gameMode)
{
    _dim = dim;
    _depth = depth;
    _gameMode = gameMode;

    //_currBoard = _utility.copyBoard(currBoard, _dim);
    _currBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _currBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _currBoard[i][j] = currBoard[i][j];
        }
    }

    _isTerminal = isTerminal();
    _move.first = move.first;
    _move.second = move.second;
    if(_gameMode == 0)
    {
        _value = calcValue();
    }
    else if(_gameMode == 1)
    {
        _value = calcValueColorsRed();
    }
    else if(_gameMode == 2)
    {
        _value = calcValueColsure();
    }
    else if(_gameMode == 3)
    {
        _value = calcValueColorsBlue();
    }

    if(!_isTerminal && !(_depth < 1))
    {
        calcChildren();
    }
}

Node::Node(const Node& other)
{
    _dim = other._dim;
    _depth = other._depth;
    _currBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _currBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _currBoard[i][j] = other._currBoard[i][j];
        }
    }
    _isTerminal = other._isTerminal;
    _move.first = other._move.first;
    _move.second = other._move.second;
    _value = other._value;
    //_children = other._children;
    for(int i = 0; i < other._children.length(); i++)
    {
        _children.append(other._children.at(i));
    }
}

Node::~Node()
{

    if(_currBoard != NULL)
    {
        for(int i = 0; i < _dim; i++)
        {
            delete _currBoard[i];
        }
        delete _currBoard;
    }

}

void Node::operator=(const Node& other)
{
    if(_currBoard != NULL)
    {
        for(int i = 0; i < _dim; i++)
        {
            delete _currBoard[i];
        }
        delete _currBoard;
    }
    _dim = other._dim;
    _depth = other._depth;
    _currBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _currBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _currBoard[i][j] = other._currBoard[i][j];
        }
    }
    _isTerminal = other._isTerminal;
    _move.first = other._move.first;
    _move.second = other._move.second;
    _value = other._value;
    //_children = other._children;
    _children.clear();
    for(int i = 0; i < other._children.length(); i++)
    {
        _children.append(other._children.at(i));
    }
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

int Node::calcValueColsure()
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
            out += 1;
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
            out += 1;
        }
    }

    if(_utility.checkTab(_utility.getDiag1(posX, posY, _currBoard, _dim)) > 1)
    {
        out += 1;
    }

    if(_utility.checkTab(_utility.getDiag2(posX, posY, _currBoard, _dim)) > 1)
    {
        out += 1;
    }

    return out;
}

int Node::calcValueColorsRed()
{
    int out = 0;
    int posX = _move.first;
    int posY = _move.second;
    int counter = 0;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[posX][i] == 0)
        {
            counter = 0;
            break;
        }
        if(_currBoard[posX][i] == -1)
        {
            counter++;
        }
    }
    out += counter;
    counter = 0;
    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[i][posY] == 0)
        {
            counter = 0;
            break;
        }
        if(_currBoard[i][posY] == -1)
        {
            counter++;
        }
    }
    out += counter;
    out += _utility.checkTabRed(_utility.getDiag1(posX, posY, _currBoard, _dim));
    out += _utility.checkTabRed(_utility.getDiag2(posX, posY, _currBoard, _dim));

    return out;
}

int Node::calcValueColorsBlue()
{
    int out = 0;
    int posX = _move.first;
    int posY = _move.second;
    int counter = 0;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[posX][i] == 0)
        {
            counter = 0;
            break;
        }
        if(_currBoard[posX][i] == 1)
        {
            counter++;
        }
    }
    out += counter;
    counter = 0;
    for(int i = 0; i < _dim; i++)
    {
        if(_currBoard[i][posY] == 0)
        {
            counter = 0;
            break;
        }
        if(_currBoard[i][posY] == 1)
        {
            counter++;
        }
    }
    out += counter;
    out += _utility.checkTabBlue(_utility.getDiag1(posX, posY, _currBoard, _dim));
    out += _utility.checkTabBlue(_utility.getDiag2(posX, posY, _currBoard, _dim));

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
                if(_gameMode == 1)
                {
                    _children.append(Node(_currBoard, QPair<int, int>(i, j), _dim, _depth - 1, 3));
                }
                else if(_gameMode == 3)
                {
                    _children.append(Node(_currBoard, QPair<int, int>(i, j), _dim, _depth - 1, 1));
                }
                else
                {
                    _children.append(Node(_currBoard, QPair<int, int>(i, j), _dim, _depth - 1, _gameMode));
                }

                _currBoard[i][j] = 0;
            }
        }
    }
}



