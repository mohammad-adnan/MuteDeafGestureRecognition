#include<iostream>
#include <vector>
using namespace std;
class Matrix
{

public:
    vector<vector<double> >matrix;
    //constructor
    Matrix(int row,int column)
    {
        matrix.resize(row);
        for(int i=0; i<row; i++)
            matrix[i].resize(column);


    }
    // to set matrix dimensions
    void SetMatrixDim(int row,int column)
    {
        matrix.resize(row);
        for(int i=0; i<row; i++)
            matrix[i].resize(column);


    }
// two matrix multiplicatiion
    Matrix  operator*(Matrix mat)
    {
        Matrix newMat(this->matrix.size(),mat.matrix[0].size());// 1 constant because the column size of input 1 forever

        for(int i=0; i<newMat.matrix.size(); i++)
        {
            for(int j=0; j<newMat.matrix[i].size(); j++)
            {
                newMat.matrix[i][j]=0;
                for(int k=0; k<this->matrix[i].size(); k++)
                {
                    newMat.matrix[i][j]+=this->matrix[i][k]*mat.matrix[k][j];
                }


            }
        }


        return newMat;
    }
    // two matrix addition

    Matrix  operator+(Matrix mat)
    {
        for(int i=0; i<this->matrix.size(); i++)
        {
            for(int j=0; j<this->matrix[i].size(); j++)
            {

                this->matrix[i][j]+=mat.matrix[i][j];
            }
        }


        return *this;
    }
};
