#include "gamewindowpve.h"
#include "ui_gamewindowpve.h"


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

    initBoard();
    _utility = Utility();

    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowPvE::GameWindowPvE(QWidget *parent, int dim, bool aiStart) :
    QMainWindow(parent),
    ui(new Ui::GameWindowPvE)
{
    ui->setupUi(this);
    _dim = dim;
    _turnNum = 0;
    _playerOneScore = 0;
    _playerTwoScore = 0;
    _depth = 3;

    initBoard();
    _utility = Utility();

    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");

    if(aiStart)
    {
        computerTurn(QPair<int, int>(-1, -1));
    }

}

GameWindowPvE::~GameWindowPvE()
{
    delete ui;
    for(int i = 0; i < _dim; i++)
    {
        delete _board[i];
    }
    delete _board;
}

void GameWindowPvE::onPushButtonClick()
{
    int posX = 0;
    int posY = 0;
    int flush = 0;

    QWidget* button =(QWidget*)(this->sender());
    int buttonIndex = ui->gridLayout->indexOf(button);
    button->setStyleSheet("background-color: blue");
    //button->update();

    ui->gridLayout->getItemPosition(buttonIndex, &posX, &posY, &flush, &flush);

    _board[posX][posY] = 1;
    _playerOneScore += updateScore(posX, posY);

    ui->label->setText("Score:"
                       "\nBluePlayer: " + QString::number(_playerOneScore) +
                       "\nRedPlayer: " + QString::number(_playerTwoScore) +
                       "\n\nCurrPlayer: Red");

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
    else
    {
        computerTurn(QPair<int, int>(posX, posY));
    }
    button->disconnect();
}

void GameWindowPvE::computerTurn(QPair<int, int> move)
{
    QPair<int, int> coords;

    Node bestNode = minimax(Node(_board, move, _dim, _depth), _depth, true);

    coords = bestNode.getMove();

    qDebug(QString::number(coords.first).toLatin1() + " " + QString::number(coords.second).toLatin1());


    QLayoutItem* button = (ui->gridLayout->itemAtPosition(coords.first, coords.second));
    button->widget()->setStyleSheet("background-color: red");

    _board[coords.first][coords.second] = 1;

    _playerTwoScore += updateScore(coords.first, coords.second);
    ui->label->setText("Score:"
                       "\nBluePlayer: " + QString::number(_playerOneScore) +
                       "\nRedPlayer: " + QString::number(_playerTwoScore) +
                       "\n\nCurrPlayer: Blue");

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
    button->widget()->disconnect();
}

Node GameWindowPvE::minimax(Node currNode, int depth, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    QVector<Node> children = currNode.getChildren();

    if(depth == 0 || currNode.getIsTerminal())
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
            if(temp.getValue() >= bestValue)
            {
                bestChild = temp;
            }
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
            if(temp.getValue() <= bestValue)
            {
                bestChild = temp;
            }
        }
        return bestChild;
    }
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
    out += _utility.checkTab(_utility.getDiag1(posX, posY, _board, _dim));
    out += _utility.checkTab(_utility.getDiag2(posX, posY, _board, _dim));
    return out;
}

void GameWindowPvE::initBoard()
{
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
}

