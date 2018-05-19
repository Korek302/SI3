#include "gamewindowpvp.h"
#include "ui_gamewindowpvp.h"


GameWindowPvP::GameWindowPvP(QWidget *parent) :
    GameWindow(parent),
    ui(new Ui::GameWindowPvP)
{
    ui->setupUi(this);

    initBoard();
    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowPvP::GameWindowPvP(QWidget *parent, int dim) :
    GameWindow(parent, dim),
    ui(new Ui::GameWindowPvP)
{
    ui->setupUi(this);

    initBoard();
    ui->label->setText("Score:"
                       "\nBluePlayer: 0"
                       "\nRedPlayer: 0"
                       "\n\nCurrPlayer: Blue");
}

GameWindowPvP::~GameWindowPvP()
{
    delete ui;
    for(int i = 0; i < _dim; i++)
    {
        delete _board[i];
    }
    delete _board;
}

void GameWindowPvP::onPushButtonClick()
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

    _board[posX][posY] = 1;
    if(player)
    {
        _playerOneScore += updateScore(posX, posY);
    }
    else
    {
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
}

void GameWindowPvP::initBoard()
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
            //_board[i][j] = 0;
        }
    }
}

