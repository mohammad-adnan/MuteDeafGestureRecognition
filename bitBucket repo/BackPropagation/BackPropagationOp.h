
#include "Matrix.cpp"
#include<vector>

#ifndef propagation
#define propagation

class BackPropagationOp
{
public:
    double LearningRate=.15;// learning rate
    Matrix inputs= Matrix(0,0);// just initialize size
    double Mse=0;    // mean square error
    Matrix outputs=Matrix(0,0);// just initialize size
    Matrix Wh=Matrix(0,0);// weights of hidden layer
    Matrix Wo=Matrix(0,0);// weights of output layer
    Matrix CurrentOutW=Matrix(0,0);

    Matrix netH=Matrix(0,0);
    Matrix netO=Matrix(0,0);

    vector<double>OutputsErros;//outputs  error terms
    vector<double> OutputsComErros;// comulative error terms
    vector<double> HiddComErros;// comulative error terms
    Matrix Bo=Matrix(0,0);// bias terms
    Matrix Bh=Matrix(0,0);
    void set(Matrix inputs,Matrix outputs,Matrix Wh,Matrix Wo,Matrix netH,Matrix netO,vector<double>OutputsErros,
             vector<double>OutputsComErros,vector<double>HiddComErros, Matrix Bh,Matrix Bo);
   // to compute net output and nethidden
    void ForwardPass();
    // to compute output errors
    void ComOutError();
    // to update weights of output layer
    void UpdateOutW();
    // to compute hidden layer errors

    void ComHiddError();
 // to update hidden layer
    void UpdateHiddW();
    // to compute mean square error
    double ComputeMse();
 // to initialize weights of output layer and hidden layer and bias
    Matrix InitMatrix(Matrix m,double a,double b);
    // to apply activation function on output layer
    void Fnet(Matrix &m);
    //  to compute comulative output errors
void   ComComOutError();


};
#endif
