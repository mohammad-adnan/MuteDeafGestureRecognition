#include<iostream>
#include<vector>
#ifndef NeuralMatrix
#define NeuralMatrix

class NeuralMatrix
{
public:
    //vector<vector<double> >matrix;
    NeuralMatrix(int row,int column);
    void SetMatrixDim(int row,int column);
// matrix multiplicatiion
    NeuralMatrix operator*(NeuralMatrix mat);
    // matrix addition
    NeuralMatrix operator+(NeuralMatrix mat);
};
#endif
