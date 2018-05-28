#include "gamewindoweve.h"
#include "ui_gamewindoweve.h"


GameWindowEvE::GameWindowEvE(QWidget *parent) :
    GameWindow(parent),
    ui(new Ui::GameWindowEvE)
{
    ui->setupUi(this);
    _depth = 0;
    _alfabeta = false;
    _red = true;

    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowEvE::GameWindowEvE(QWidget *parent, int dim, bool aiStart, int depth, bool alfabeta, int gameMode, int nodeTraversal) :
    GameWindow(parent, dim),
    ui(new Ui::GameWindowEvE)
{
    ui->setupUi(this);
    _depth = depth;
    _alfabeta = alfabeta;
    _red = aiStart;
    _gameMode = gameMode;
    _nodeTraversal = nodeTraversal;

    initBoard();

    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Red");
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(onPushButtonClick()));
}

GameWindowEvE::~GameWindowEvE()
{
    delete ui;
    for(int i = 0; i < _dim; i++)
    {
        delete _board[i];
    }
    delete _board;
}

void GameWindowEvE::onPushButtonClick()
{
    computerTurn(QPair<int, int>(-1, -1));
}

void GameWindowEvE::computerTurn(QPair<int, int> move)
{
    QPair<int, int> coords;

    if(_nodeTraversal == 0)
    {
        if(_alfabeta)
        {
            coords = alfabeta(Node(_board, move, _dim, _depth, _gameMode),
                              _depth, std::numeric_limits<int>::min(),
                              std::numeric_limits<int>::max(), true).getMove();
        }
        else
        {
            coords = minimax(Node(_board, move, _dim, _depth, _gameMode), _depth, true).getMove();
        }
    }
    else if(_nodeTraversal == 1)
    {
        if(_alfabeta)
        {
            coords = alfabetaRandChildPick(Node(_board, move, _dim, _depth, _gameMode),
                              _depth, std::numeric_limits<int>::min(),
                              std::numeric_limits<int>::max(), true).getMove();
        }
        else
        {
            coords = minimaxRandChildPick(Node(_board, move, _dim, _depth, _gameMode), _depth, true).getMove();
        }
    }


    qDebug(QString::number(coords.first).toLatin1() + " " + QString::number(coords.second).toLatin1());


    QLayoutItem* button = (ui->gridLayout->itemAtPosition(coords.first, coords.second));

    if(_red)
    {
        button->widget()->setStyleSheet("background-color: red");
        _board[coords.first][coords.second] = -1;
        if(_gameMode == 0)
        {
            _playerTwoScore += updateScore(coords.first, coords.second);
        }
        else if(_gameMode == 1)
        {
            _playerTwoScore += updateScoreColorsRed(coords.first, coords.second);
        }
        else if(_gameMode == 2)
        {
            _playerTwoScore += updateScoreClosure(coords.first, coords.second);
        }
        ui->label->setText("Score:"
                           "\nBluePlayer: " + QString::number(_playerTwoScore) +
                           "\nRedPlayer: " + QString::number(_playerOneScore) +
                           "\n\nCurrPlayer: Blue");
    }
    else
    {
        button->widget()->setStyleSheet("background-color: blue");
        _board[coords.first][coords.second] = 1;
        if(_gameMode == 0)
        {
            _playerOneScore += updateScore(coords.first, coords.second);
        }
        else if(_gameMode == 1)
        {
            _playerOneScore += updateScoreColorsRed(coords.first, coords.second);
        }
        else if(_gameMode == 2)
        {
            _playerOneScore += updateScoreClosure(coords.first, coords.second);
        }
        ui->label->setText("Score:"
                           "\nBluePlayer: " + QString::number(_playerTwoScore) +
                           "\nRedPlayer: " + QString::number(_playerOneScore) +
                           "\n\nCurrPlayer: Red");
    }

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
        button->widget()->disconnect();

        qApp->processEvents();
        _red = !_red;
        computerTurn(coords);
    }
}

Node GameWindowEvE::alfabeta(Node currNode, int depth, int alfa, int beta, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    if(depth == 0 || currNode.getIsTerminal())
    {
        return currNode;
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        foreach(Node n, currNode.getChildren())
        {
            Node temp = alfabeta(n, depth - 1, alfa, beta, false);
            bestValue = std::max(bestValue, temp.getValue());
            if(temp.getValue() >= bestValue)
            {
                bestChild = temp;
            }
            alfa = std::max(alfa, bestValue);
            if(beta <= alfa)
            {
                break;
            }
        }
        return bestChild;
    }
    else
    {
        bestValue = std::numeric_limits<int>::max();
        foreach(Node n, currNode.getChildren())
        {
            Node temp = alfabeta(n, depth - 1, alfa, beta, true);
            bestValue = std::min(bestValue, temp.getValue());
            if(temp.getValue() <= bestValue)
            {
                bestChild = temp;
            }
            beta = std::min(beta, bestValue);
            if(beta <= alfa)
            {
                break;
            }
        }
        return bestChild;
    }
}

Node GameWindowEvE::alfabetaRandChildPick(Node currNode, int depth, int alfa, int beta, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    if(depth == 0 || currNode.getIsTerminal())
    {
        return currNode;
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        int counter = 0;
        QVector<int> indices;
        while(counter < currNode.getChildren().size())
        {
            int i = rand() % currNode.getChildren().size();
            while(indices.contains(i))
            {
                i = rand() % currNode.getChildren().size();
            }
            indices.append(i);

            Node n = currNode.getChildren().at(i);
            Node temp = alfabetaRandChildPick(n, depth - 1, alfa, beta, false);
            bestValue = std::max(bestValue, temp.getValue());
            if(temp.getValue() >= bestValue)
            {
                bestChild = temp;
            }
            alfa = std::max(alfa, bestValue);
            if(beta <= alfa)
            {
                break;
            }
            counter++;
        }
        return bestChild;
    }
    else
    {
        bestValue = std::numeric_limits<int>::max();
        int counter = 0;
        QVector<int> indices;
        while(counter < currNode.getChildren().size())
        {
            int i = rand() % currNode.getChildren().size();
            while(indices.contains(i))
            {
                i = rand() % currNode.getChildren().size();
            }
            indices.append(i);

            Node n = currNode.getChildren().at(i);
            Node temp = alfabetaRandChildPick(n, depth - 1, alfa, beta, true);
            bestValue = std::min(bestValue, temp.getValue());
            if(temp.getValue() <= bestValue)
            {
                bestChild = temp;
            }
            beta = std::min(alfa, bestValue);
            if(beta <= alfa)
            {
                break;
            }
            counter++;
        }
        return bestChild;
    }
}

Node GameWindowEvE::minimax(Node currNode, int depth, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    if(depth == 0 || currNode.getIsTerminal())
    {
        return currNode;
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        foreach(Node n, currNode.getChildren())
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
        foreach(Node n, currNode.getChildren())
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

Node GameWindowEvE::minimaxRandChildPick(Node currNode, int depth, bool maximizingPlayer)
{
    int bestValue;
    Node bestChild;

    if(depth == 0 || currNode.getIsTerminal())
    {
        return currNode;
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        int counter = 0;
        QVector<int> indices;
        while(counter < currNode.getChildren().size())
        {
            int i = rand() % currNode.getChildren().size();
            while(indices.contains(i))
            {
                i = rand() % currNode.getChildren().size();
            }
            indices.append(i);

            Node n = currNode.getChildren().at(i);
            Node temp = minimax(n, depth - 1, false);
            bestValue = std::max(bestValue, temp.getValue());
            if(temp.getValue() >= bestValue)
            {
                bestChild = temp;
            }
            counter++;
        }
        return bestChild;
    }
    else
    {
        bestValue = std::numeric_limits<int>::max();
        int counter = 0;
        QVector<int> indices;
        while(counter < currNode.getChildren().size())
        {
            int i = rand() % currNode.getChildren().size();
            while(indices.contains(i))
            {
                i = rand() % currNode.getChildren().size();
            }
            indices.append(i);

            Node n = currNode.getChildren().at(i);
            Node temp = minimax(n, depth - 1, true);
            bestValue = std::min(bestValue, temp.getValue());
            if(temp.getValue() <= bestValue)
            {
                bestChild = temp;
            }
            counter++;
        }
        return bestChild;
    }
}

void GameWindowEvE::initBoard()
{
    for(int i = 0; i < _dim; i++)
    {
        for(int j = 0; j < _dim; j++)
        {
            QPushButton* button = new QPushButton(" ");
            button->setMaximumHeight(button->width());
            ui->gridLayout->addWidget(button, i, j);
        }
    }
}

