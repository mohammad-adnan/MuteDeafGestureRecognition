
#include "Matrix.cpp"
#include<vector>

#ifndef propagation
#define propagation

class BackPropagationOp
{
public:
	BackPropagationOp():LearningRate(.4),Mse(0),inputs(0,0),outputs(0,0),Wh(0,0),Wo(0,0)
		,CurrentOutW(0,0),netH(0,0),netO(0,0),Bo(0,0),Bh(0,0){

	}
    double LearningRate;
    Matrix inputs;// just initialize size
    double Mse;
    Matrix outputs;// just initialize size
    Matrix Wh;
    Matrix Wo;
    Matrix CurrentOutW;

    Matrix netH;
    Matrix netO;

    vector<double>OutputsErros;//outputs  error terms
    vector<double> OutputsComErros;// comulative error terms
    vector<double> HiddComErros;// comulative error terms
    Matrix Bo;
    Matrix Bh;
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
