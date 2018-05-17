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

    _prevBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _prevBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _prevBoard[i][j] = 0;
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
    _depth = 5;

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

    _prevBoard = new int*[_dim];
    for(int i = 0; i < _dim; i++)
    {
        _prevBoard[i] = new int[_dim];
        for(int j = 0; j < _dim; j++)
        {
            _prevBoard[i][j] = 0;
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

    QWidget* button =(QWidget*)(this->sender());
    int buttonIndex = ui->gridLayout->indexOf(button);
    button->setStyleSheet("background-color: blue");
    //button->update();

    ui->gridLayout->getItemPosition(buttonIndex, &posX, &posY, &flush, &flush);

    _prevBoard = copyBoard(_board);
    updateBoard(posX, posY, 1);
    _playerOneScore += updateScore(posX, posY);

    QString currPlayerColor = "Red";
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

    computerTurn(QPair<int, int>(posX, posY));
}

void GameWindowPvE::computerTurn(QPair<int, int> move)
{
    QPair<int, int> coords;
    //showBoard(_board);

    //Node bestNode = minimax(Node(_board, diffSpots(_prevBoard, _board), _dim, _depth), _depth, true);
    //showBoard(bestNode.getCurrBoard());

    Node currNode = Node(_board, move, _dim, _depth);
    Node bestNode = minimaxNode(currNode, minimaxBestVal(currNode, _depth, true));

    coords = bestNode.getMove();//diffSpots(_board, bestNode.getCurrBoard());

    qDebug(QString::number(coords.first).toLatin1() + " " + QString::number(coords.second).toLatin1());


    QLayoutItem* button = (ui->gridLayout->itemAtPosition(coords.first, coords.second));
    button->widget()->setStyleSheet("background-color: red");

    _prevBoard = copyBoard(_board);
    updateBoard(coords.first, coords.second, 1);

    _playerTwoScore = updateScore(coords.first, coords.second);
    ui->label->setText("Score:"
                       "\nBluePlayer: " + QString::number(_playerOneScore) +
                       "\nRedPlayer: " + QString::number(_playerTwoScore) +
                       "\n\nCurrPlayer: Blue");
    //ui->label->setText(QString::number(coords.first)+" - "+QString::number(coords.second));

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

int GameWindowPvE::minimaxBestVal(Node currNode, int depth, bool maximizingPlayer)
{
    int bestValue;

    QVector<Node> children = currNode.getChildren();

    if(depth == 0 || currNode.isTerminal())
    {
        return currNode.getValue();
    }
    if(maximizingPlayer)
    {
        bestValue = std::numeric_limits<int>::min();
        foreach(Node n, children)
        {
            int v = minimaxBestVal(n, depth - 1, false);
            bestValue = std::max(bestValue, v);
        }
        return bestValue;
    }
    else
    {
        bestValue = std::numeric_limits<int>::max();
        foreach(Node n, children)
        {
            int v = minimaxBestVal(n, depth - 1, true);
            bestValue = std::min(bestValue, v);
        }
        return bestValue;
    }
}

Node GameWindowPvE::minimaxNode(Node currNode, int bestValue)
{
    Node out;
    QVector<Node> children = currNode.getChildren();
    foreach(Node n, children)
    {
        if(n.getValue() == bestValue)
        {
            out = n;
            return out;
        }
    }
    qDebug("ehhhhhhhhhhhhhhhhhhhhh");
    return out;
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

QPair<int, int> GameWindowPvE::diffSpots(int** tab1, int** tab2)
{
    QPair<int, int> out(-1, -1);
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

int** GameWindowPvE::copyBoard(int** original)
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

void GameWindowPvE::showBoard(int** original)
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







