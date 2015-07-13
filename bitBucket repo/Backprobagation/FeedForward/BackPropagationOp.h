
#include "Matrix.cpp"
#include<vector>

#ifndef propagation
#define propagation

class BackPropagationOp
{
public:
    double LearningRate=.4;
    Matrix inputs= Matrix(0,0);// just initialize size
    double Mse=0;
    Matrix outputs=Matrix(0,0);// just initialize size
    Matrix Wh=Matrix(0,0);
    Matrix Wo=Matrix(0,0);
    Matrix CurrentOutW=Matrix(0,0);

    Matrix netH=Matrix(0,0);
    Matrix netO=Matrix(0,0);

    vector<double>OutputsErros;//outputs  error terms
    vector<double> OutputsComErros;// comulative error terms
    vector<double> HiddComErros;// comulative error terms
    Matrix Bo=Matrix(0,0);
    Matrix Bh=Matrix(0,0);
   void  set(Matrix inputs,Matrix outputs,Matrix Wh,Matrix Wo,vector<double>OutputsErros,
                             vector<double>OutputsComErros,vector<double>HiddComErros);
                              void ForwardPass();
    void ComOutError();
    void UpdateOutW();
    void ComHiddError();
    void UpdateHiddW();
    double ComputeMse();
    Matrix InitMatrix(Matrix m,double a,double b);
    void Fnet(Matrix &m);
void   ComComOutError();


};
#endif
