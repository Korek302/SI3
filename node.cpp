#include "node.h"


private:
int** _prevBoard;
int** _currBoard;
QVector<Node> _children;
int value;

Node::Node(int** currBoard, int dim)
{
    _value = 0;

    _currBoard = new int*[dim];
    for(int i = 0; i < dim; i++)
    {
        _currboard[i] = new int[dim];
        for(int j = 0; j < dim; j++)
        {
            _currboard[i][j] = currBoard[i][j];
            if(_currboard[i][j] == 0)
            {
                _currboard[i][j] = 1;
                _children.append(Node(_currBoard, dim));

                _currboard[i][j] = 0;
            }
        }
    }

    _prevBoard = new int*[dim];
    for(int i = 0; i < dim; i++)
    {
        _prevBoard[i] = new int[dim];
        for(int j = 0; j < dim; j++)
        {
            _prevBoard[i][j] = 0;
        }
    }
}

Node::Node(int** currBoard, int givenValue, int dim)
{

}

Node::Node(int** currBoard, int** prevBoard, int dim)
{
    int** tempCopy = new int*[dim];
    for(int k = 0; k < dim; k++)
    {
        tempCopy[k] = new int[dim];
        for(int l = 0; l < dim; l++)
        {
            tempCopy[k][l] = _currboard[k][l];
        }
    }

    _currBoard = new int*[dim];
    for(int i = 0; i < dim; i++)
    {
        _currboard[i] = new int[dim];
        for(int j = 0; j < dim; j++)
        {
            _currboard[i][j] = currBoard[i][j];
            if(_currboard[i][j] == 0)
            {
                tempCopy[i][j] = 1;
                _children.append(Node(tempCopy, currBoard, dim));

                tempCopy[i][j] = 0;
            }
        }
    }

    _prevBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _prevBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _prevBoard[i][j] = prevBoard[i][j];
        }
    }

    _value
}

Node::Node(int** currBoard, int** prevBoard, int givenValue, int dim)
{

}

bool Node::isTerminal()
{

}

int Node::getValue()
{

}

void Node::setValue()
{

}

int** Node::getCurrBoard()
{

}

QVector<Node> Node::getChildren()
{

}

void Node::calcChildren()
{

}

void Node::calcValue()
{

}
