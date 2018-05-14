#include "gamewindowpve.h"
#include "ui_gamewindowpve.h"

#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <string.h>
#include <vector>

GameWindowPvE::GameWindowPvE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindowPvE)
{
    ui->setupUi(this);
    _dim = 0;
    _turnNum = 0;
    _playerOneScore = 0;
    _playerTwoScore = 0;
    _depth = 3;

    _board = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _board[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            QPushButton* button = new QPushButton(" ");
            connect(button,SIGNAL(released()),this,SLOT(onPushButtonClick()));
            button->setMaximumHeight(button->width());
            ui->gridLayout->addWidget(button, i, j);
            _board[i][j] = 0;
        }
    }
    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowPvE::GameWindowPvE(QWidget *parent, int dim) :
    QMainWindow(parent),
    ui(new Ui::GameWindowPvE)
{
    ui->setupUi(this);
    _dim = dim;
    _turnNum = 0;
    _playerOneScore = 0;
    _playerTwoScore = 0;
    _depth = 3;

    _board = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _board[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            QPushButton* button = new QPushButton(" ");
            connect(button,SIGNAL(released()),this,SLOT(onPushButtonClick()));
            button->setMaximumHeight(button->width());
            ui->gridLayout->addWidget(button, i, j);
            _board[i][j] = 0;
        }
    }
    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowPvE::~GameWindowPvE()
{
    delete ui;
}

void GameWindowPvE::onPushButtonClick()
{
    int posX = 0;
    int posY = 0;
    int flush = 0;
    bool player = _turnNum % 2 == 0?true:false;
    QWidget* button =(QWidget*)(this->sender());
    int buttonIndex = ui->gridLayout->indexOf(button);

    if(player)
    {
        button->setStyleSheet("background-color: blue");
    }
    else
    {
        button->setStyleSheet("background-color: red");
    }
    //button->update();

    ui->gridLayout->getItemPosition(buttonIndex, &posX, &posY, &flush, &flush);

    updateBoard(posX, posY, player?1:-1);
    if(player)
    {
        updateBoard(posX, posY, 1);
        _playerOneScore += updateScore(posX, posY);
    }
    else
    {
        updateBoard(posX, posY, -1);
        _playerTwoScore += updateScore(posX, posY);
    }
    QString currPlayerColor = player ? "Red" : "Blue";
    ui->label->setText("Score:"
                       "\nBluePlayer: " + QString::number(_playerOneScore) +
                       "\nRedPlayer: " + QString::number(_playerTwoScore) +
                       "\n\nCurrPlayer: " + currPlayerColor);

    _turnNum++;

    if(_turnNum > _dim*_dim - 1)
    {
        qDebug("koniec");
        if(_playerOneScore > _playerTwoScore)
        {
            ui->label->setText("Winner: Blue");
        }
        else if(_playerOneScore < _playerTwoScore)
        {
            ui->label->setText("Winner: Red");
        }
        else
        {
            ui->label->setText("Tie");
        }
    }
    button->disconnect();

    computerTurn();
}

void GameWindowPvE::updateBoard(int posX, int posY, int val)
{
    _board[posX][posY] = val;
}

int GameWindowPvE::updateScore(int posX, int posY)
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
    out += checkTab(getDiag1(posX, posY));
    out += checkTab(getDiag2(posX, posY));
    return out;
}

QVector<int> GameWindowPvE::getDiag1(int rowId, int colId)
{
    QVector<int> out1;
    int tempI = rowId;
    int tempJ = colId;
    while (tempI >= 0 && tempJ >= 0)
    {
        out1.push_back(_board[tempI][tempJ]);
        tempI--;
        tempJ--;
    }
    tempI = rowId + 1;
    tempJ = colId + 1;
    while (tempI < _dim && tempJ < _dim)
    {
        out1.push_back(_board[tempI][tempJ]);
        tempI++;
        tempJ++;
    }
    return out1;
}

QVector<int> GameWindowPvE::getDiag2(int rowId, int colId)
{
    QVector<int> out1;
    int tempI = rowId - 1;
    int tempJ = colId + 1;
    while (tempI >= 0 && tempJ < _dim)
    {
        out1.push_back(_board[tempI][tempJ]);
        tempI--;
        tempJ++;
    }
    tempI = rowId;
    tempJ = colId;
    while (tempI < _dim && tempJ >= 0)
    {
        out1.push_back(_board[tempI][tempJ]);
        tempI++;
        tempJ--;
    }
    return out1;
}

int GameWindowPvE::checkTab(QVector<int> row)
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

void GameWindowPvE::computerTurn()
{
    QPair<int, int> coords;

    Node bestNode = minimax(new Node(_board, _prevBoard), _depth, true);

    coords = diffSpot(_board, bestNode.getCurrBoard());

    updateBoard(coords.first, coords.second, -1);
    updateScore(coords.first, coords.second);
}

QPair<int, int> GameWindowPvE::minimaxCoords()
{
    QPair<int, int> coords;
    Node bestChild;
    Node currNode = new Node(_board, _prevBoard);
    int bestValue = minimax(currNode, _depth, true);

    QVector<Node> children = currNode.getChildren();


    foreach(Node n, children)
    {

    }

    return coords;
}

Node GameWindowPvE::minimax(Node currNode, int depth, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    QVector<Node> children = currNode.getChildren();

    if(depth == 0 || currNode.isTerminal())
    {
        return currNode;
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        foreach(Node n, children)
        {
            Node temp = minimax(n, depth - 1, false);
            bestValue = std::max(bestValue, temp.getValue());
            if(temp.getValue() > bestValue)
            {
                bestChild = temp;
            }
            else
            {
                bestChild = currNode;
            }

            //int v = minimax(n, depth - 1, false);
            //bestValue = std::max(bestValue, v);
        }
        return bestChild;
    }
    else
    {
        bestValue = std::numeric_limits<int>::max();
        foreach(Node n, children)
        {
            Node temp = minimax(n, depth - 1, true);
            bestValue = std::min(bestValue, temp.getValue());
            if(temp.getValue() < bestValue)
            {
                bestChild = temp;
            }
            else
            {
                bestChild = currNode;
            }

            //int v = minimax(n, depth - 1, true);
            //bestValue = std::min(bestValue, v);
        }
        return bestChild;
    }
}

QPair<int, int> GameWindowPvE::diffSpots(int** tab1, int** tab2)
{
    QPair<int, int> out = new QPair<int, int>(0, 0);
    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            if(tab1[i][j] != tab2[i][j])
            {
                out.first = i;
                out.second = j;
                return out;
            }
        }
    }
    return out;
}











