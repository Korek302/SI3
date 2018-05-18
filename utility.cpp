#include "utility.h"

Utility::Utility()
{}


Utility::~Utility()
{}

QVector<int> Utility::getDiag1(int rowId, int colId, int** board, int dim)
{
    QVector<int> out1;
    int tempI = rowId;
    int tempJ = colId;
    while (tempI >= 0 && tempJ >= 0)
    {
        out1.push_back(board[tempI][tempJ]);
        tempI--;
        tempJ--;
    }
    tempI = rowId + 1;
    tempJ = colId + 1;
    while (tempI < dim && tempJ < dim)
    {
        out1.push_back(board[tempI][tempJ]);
        tempI++;
        tempJ++;
    }
    return out1;
}

QVector<int> Utility::getDiag2(int rowId, int colId, int** board, int dim)
{
    QVector<int> out1;
    int tempI = rowId - 1;
    int tempJ = colId + 1;
    while (tempI >= 0 && tempJ < dim)
    {
        out1.push_back(board[tempI][tempJ]);
        tempI--;
        tempJ++;
    }
    tempI = rowId;
    tempJ = colId;
    while (tempI < dim && tempJ >= 0)
    {
        out1.push_back(board[tempI][tempJ]);
        tempI++;
        tempJ--;
    }
    return out1;
}

int Utility::checkTab(QVector<int> row)
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

int** Utility::copyBoard(int** original, int dim)
{
    int** out = new int*[dim];
    for(int i = 0; i < dim; i++)
    {
        out[i] = new int[dim];
        for(int j = 0; j < dim; j++)
        {
            out[i][j] = original[i][j];
        }
    }
    return out;
}

QPair<int, int> Utility::diffSpots(int** tab1, int** tab2, int dim)
{
    QPair<int, int> out(-1, -1);
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
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

void Utility::showBoard(int** original, int dim)
{
    QString str = "";
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            str += (QString::number(original[i][j]) + " ");
        }
        qDebug(str.toLatin1());
        str = "";
    }
    qDebug("\n");
}
