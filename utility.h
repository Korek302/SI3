#ifndef UTILITY_H
#define UTILITY_H

#include <QVector>
#include <QPair>

class Utility
{
public:
    Utility();
    ~Utility();

    int checkTab(QVector<int> row);
    int** copyBoard(int** original, int dim);
    QVector<int> getDiag1(int rowId, int colId, int** board, int dim);
    QVector<int> getDiag2(int rowId, int colId, int** board, int dim);
    QPair<int, int> diffSpots(int** tab1, int** tab2, int dim);
    void showBoard(int** original, int dim);

private:
};

#endif // UTILITY_H
