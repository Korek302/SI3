#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QVector>
#include <string.h>


namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent);
    explicit GameWindow(QWidget *parent, int dim);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    int _dim;
    int** _board;
    int _turnNum;
    int _playerOneScore;
    int _playerTwoScore;

    void updateBoard(int posX, int posY, int val);
    QVector<int> getDiag1(int rowId, int colId);
    QVector<int> getDiag2(int rowId, int colId);
    int checkTab(QVector<int> row);
    int updateScore(int posX, int posY);

private slots:
    void onPushButtonClick();
};

#endif // GAMEWINDOW_H
