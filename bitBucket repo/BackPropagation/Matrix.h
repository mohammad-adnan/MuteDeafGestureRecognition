#include<iostream>
#include<vector>
#ifndef matrix
#define matrix

class Matrix
{
public:
    //vector<vector<double> >matrix;
    Matrix(int row,int column);
    // to set matrix dimensions

    void SetMatrixDim(int row,int column);
// matrix multiplicatiion
    Matrix operator*(Matrix mat);
    // matrix addition
    Matrix operator+(Matrix mat);
};
#endif
