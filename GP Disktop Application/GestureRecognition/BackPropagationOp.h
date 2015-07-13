
#include "NeuralMatrix.cpp"
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
    NeuralMatrix inputs;// just initialize size
    double Mse;
    NeuralMatrix outputs;// just initialize size
   NeuralMatrix Wh;
   NeuralMatrix Wo;
    NeuralMatrix CurrentOutW;

    NeuralMatrix netH;
    NeuralMatrix netO;

    vector<double>OutputsErros;//outputs  error terms
    vector<double> OutputsComErros;// comulative error terms
    vector<double> HiddComErros;// comulative error terms
    NeuralMatrix Bo;
   NeuralMatrix Bh;
   void  set(NeuralMatrix inputs,NeuralMatrix outputs,NeuralMatrix Wh,NeuralMatrix Wo,vector<double>OutputsErros,
                             vector<double>OutputsComErros,vector<double>HiddComErros);
                              void ForwardPass();
    void ComOutError();
    void UpdateOutW();
    void ComHiddError();
    void UpdateHiddW();
    double ComputeMse();
    NeuralMatrix InitMatrix(NeuralMatrix m,double a,double b);
    void Fnet(NeuralMatrix &m);
void   ComComOutError();


};
#endif
