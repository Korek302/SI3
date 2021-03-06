#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _dim = 0;
    _turnNum = 0;
    _playerOneScore = 0;
    _playerTwoScore = 0;

    initBoard();
}

GameWindow::GameWindow(QWidget *parent, int dim) :
    QMainWindow(parent)
{
    _dim = dim;
    _turnNum = 0;
    _playerOneScore = 0;
    _playerTwoScore = 0;

    initBoard();
}

GameWindow::~GameWindow()
{
    for(int i = 0; i < _dim; i++)
    {
        delete _board[i];
    }
    delete _board;
}

int GameWindow::updateScore(int posX, int posY)
{
    int out = 0;
    for(int i = 0; i < _dim; i++)
    {
        if(_board[posX][i] == 0)
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
        if(_board[i][posY] == 0)
        {
            break;
        }
        if(i == _dim - 1)
        {
            out += _dim;
        }
    }
    out += _utility.checkTab(_utility.getDiag1(posX, posY, _board, _dim));
    out += _utility.checkTab(_utility.getDiag2(posX, posY, _board, _dim));
    return out;
}

int GameWindow::updateScoreClosure(int posX, int posY)
{
    int out = 0;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_board[posX][i] == 0)
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
        if(_board[i][posY] == 0)
        {
            break;
        }
        if(i == _dim - 1)
        {
            out += 1;
        }
    }

    if(_utility.checkTab(_utility.getDiag1(posX, posY, _board, _dim)) > 1)
    {
        out += 1;
    }

    if(_utility.checkTab(_utility.getDiag2(posX, posY, _board, _dim)) > 1)
    {
        out += 1;
    }

    return out;
}

int GameWindow::updateScoreColorsRed(int posX, int posY)
{
    int out = 0;
    int counter = 0;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_board[posX][i] == 0)
        {
            counter = 0;
            break;
        }
        if(_board[posX][i] == -1)
        {
            counter++;
        }
    }
    out += counter;
    counter = 0;
    for(int i = 0; i < _dim; i++)
    {
        if(_board[i][posY] == 0)
        {
            counter = 0;
            break;
        }
        if(_board[i][posY] == -1)
        {
            counter++;
        }
    }
    out += counter;
    out += _utility.checkTabRed(_utility.getDiag1(posX, posY, _board, _dim));
    out += _utility.checkTabRed(_utility.getDiag2(posX, posY, _board, _dim));

    return out;
}

int GameWindow::updateScoreColorsBlue(int posX, int posY)
{
    int out = 0;
    int counter = 0;
    if(posX == -1 && posY == -1)
    {
        return 0;
    }

    for(int i = 0; i < _dim; i++)
    {
        if(_board[posX][i] == 0)
        {
            counter = 0;
            break;
        }
        if(_board[posX][i] == 1)
        {
            counter++;
        }
    }
    out += counter;
    counter = 0;
    for(int i = 0; i < _dim; i++)
    {
        if(_board[i][posY] == 0)
        {
            counter = 0;
            break;
        }
        if(_board[i][posY] == 1)
        {
            counter++;
        }
    }
    out += counter;
    out += _utility.checkTabBlue(_utility.getDiag1(posX, posY, _board, _dim));
    out += _utility.checkTabBlue(_utility.getDiag2(posX, posY, _board, _dim));

    return out;
}

void GameWindow::initBoard()
{
    _board = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _board[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _board[i][j] = 0;
        }
    }
}
