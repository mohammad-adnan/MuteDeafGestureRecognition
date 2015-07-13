#include<vector>
#include<math.h>
#include <iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include <iostream>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <cctype>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <set>
#include <map>
#include <numeric>
#include <utility>
#include <deque>
#include <queue>
#include <stack>
#include <iomanip>
#include <complex>
#include <list>
#include <bitset>
#include <fstream>
#include <limits>
#include <memory.h>
#include<conio.h>
#include <string>
#include<ctime>
#include "BackPropagationOp.h"



void BackPropagationOp:: set(Matrix inputs,Matrix outputs,Matrix Wh,Matrix Wo,Matrix netH,Matrix netO,vector<double>OutputsErros,
                             vector<double>OutputsComErros,vector<double>HiddComErros, Matrix Bh,Matrix Bo)
{
    this->inputs=inputs;
    this->outputs=outputs;
    this->Wh=Wh;
    this->Wo=Wo;
    this->netH=netH;
    this->netO=netO;
    this->OutputsErros=OutputsErros;
    this->OutputsComErros=OutputsComErros;
    this->Bh=Bh;
    this->Bo=Bo;

    this->HiddComErros=HiddComErros;
    CurrentOutW=Wo;
}
// compute outputs
void BackPropagationOp::  ForwardPass()
{
//compute neth
    netH=Wh*inputs;
// add bias

    netH=netH+Bh;


// get f of net hidden

    Fnet(netH);
//compute neto
    netO=Wo*netH;
// add bias

    netO=netO+Bo;
    Fnet(netO);
}
// compute error term of outputs
void BackPropagationOp::  ComOutError()
{
// error=actualoutputs-computesdoutputs;
//    cout<<endl<<" size "<<OutputsErros.size();
    for(int i=0; i<this->OutputsErros.size(); i++)
    {
        OutputsErros[i]=outputs.matrix[i][0]-netO.matrix[i][0];
    }
    // compute comulative error terms
    //comulative  output error=function of net outputerrorK *
    // function is derivative sigmoid function
    for(int i=0; i<this->OutputsComErros.size(); i++)
    {
        OutputsComErros[i]=netO.matrix[i][0]*(1-netO.matrix[i][0])*OutputsErros[i];

    }

}
void BackPropagationOp::  ComComOutError()
{
    for(int i=0; i<this->OutputsComErros.size(); i++)
    {
        OutputsComErros[i]=netO.matrix[i][0]*(1-netO.matrix[i][0])*OutputsErros[i];
    }
}


// update the weights of outputs
void BackPropagationOp:: UpdateOutW()
{
    // delta rule for output layer
    for(int i=0; i<Wo.matrix.size(); i++)
    {
         //   Bo.matrix[i][0]+= (this->LearningRate*OutputsComErros[i]*netO.matrix[i][0]);
        for(int j=0; j<Wo.matrix[i].size(); j++)
        {
            Wo.matrix[i][j]=Wo.matrix[i][j]+(this->LearningRate*OutputsComErros[i]*netH.matrix[j][0]);

        }
    }



}

// compute error term of hidden layer
void BackPropagationOp:: ComHiddError()
{
    //cout<<endl<<" hidden error"<<endl;
    // compute comulative error terms of hidden layer
    //comulative  hidden error=function of net outputerrorK *
    // function is derivative sigmoid function
    double value=0;
    for(int i=0; i<this->HiddComErros.size(); i++)
    {
        value=0;
        HiddComErros[i]=netH.matrix[i][0]*(1-netH.matrix[i][0]);

        for(int j=0; j<this->OutputsErros.size(); j++)
        {
            value+=this->OutputsErros[j]*CurrentOutW.matrix[j][i];

        }
        HiddComErros[i]*=value;
    }


}


// update the weights of hidden layer
void BackPropagationOp:: UpdateHiddW()
{
    // delta rule for Hidden layer
    //      cout<<endl<<" updated hidden layer"<<endl;
    for(int i=0; i<Wh.matrix.size(); i++)
    {
//Bh.matrix[i][0]+= (this->LearningRate*HiddComErros[i]*netO.matrix[i][0]);

        for(int j=0; j<Wh.matrix[i].size(); j++)
        {
            Wh.matrix[i][j]=Wh.matrix[i][j]+(this->LearningRate*HiddComErros[i]*inputs.matrix[j][0]);

        }
    }


}


double BackPropagationOp:: ComputeMse()
{

    double mse=0;
    for(int i=0; i<OutputsErros.size(); i++)
        mse+=(OutputsErros[i]*OutputsErros[i]);
    mse/=2;
    CurrentOutW=Wo;
    return mse;
}

///// initialize weghts and bias
Matrix BackPropagationOp:: InitMatrix(Matrix m,double a,double b)
{

    for(int i=0; i<m.matrix.size(); i++)
    {
        for(int j=0; j<m.matrix[i].size(); j++)
        {

            m.matrix[i][j]=((rand()%int(b-a))+a)+(double(rand()%1000)/(double)1000);
        }
    }
    return m;
}
// to get f of net hidden
void BackPropagationOp:: Fnet(Matrix &m)
{
    for(int i=0; i<m.matrix.size(); i++)
        for(int j=0; j<m.matrix[i].size(); j++)
        {
            {

                m.matrix[i][j]=1/(1+exp(-1*m.matrix[i][j]));
            }

        }


}






