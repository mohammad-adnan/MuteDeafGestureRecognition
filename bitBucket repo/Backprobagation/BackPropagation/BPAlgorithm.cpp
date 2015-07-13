#include<vector>
#include<math.h>
#include <algorithm>
#include <string>
#include<time.h>
#include <iostream>
#include <fstream>
#include"BPAlgorithm.h"
using namespace std;

double BPAlgorithm:: scale(double x,double xmin,double xmax)
{

    return (x-xmin)/(xmax-xmin);
}


double BPAlgorithm:: descale(double x,double xmin,double xmax)
{

    return xmin+(x*(xmax-xmin));
}

void BPAlgorithm:: run()
{
    srand(time(NULL));
    freopen("output.txt","w",stdout);
    freopen("train.txt","r",stdin);
    double Mse=0,BestMse=99999999999;
    int m,l,n,k;
    cin>>m>>l>>n>>k;
    Matrix dataSet(k,m+n);
    vector<pair<double ,double> >maxmin(m+n);



    for(int i=0; i<maxmin.size(); i++)
    {
        maxmin[i].first=99999999;// any big number
        maxmin[i].second=0;

    }



    for(int i=0; i<k; i++)
    {

        for(int h=0; h<m+n; h++)
        {

            cin>>dataSet.matrix[i][h];


            if(dataSet.matrix[i][h]>maxmin[h].second)
                maxmin[h].second=dataSet.matrix[i][h];
            if(dataSet.matrix[i][h]<maxmin[h].first)
                maxmin[h].first=dataSet.matrix[i][h];




        }
    }
    int Iterations=0;
    Matrix Wh(l,m);
    Matrix Wo(n,l);

    Matrix BestWh(l,m);
    Matrix BestWo(n,l);
    Matrix BestBo(n,1);
    Matrix BestBh(l,1);

    Matrix Bo(n,1);
    Matrix Bh(l,1);


    BackPropagationOp initial;
    for(int tt=0; tt<200; tt++)
    {
        Iterations=0;
        Wh=initial.InitMatrix(Wh,-1,1);

        Wo=initial.InitMatrix(Wo,-1,1);

        Bh=initial.InitMatrix(Bh,-1,1);

        Bo=initial.InitMatrix(Bo,-1,1);

          /*  for(int i=0; i<Wh.matrix.size(); i++)
                 {
                     for(int j=0; j<Wh.matrix[i].size(); j++)
                     {
                         cout<<Wh.matrix[i][j]<<" ";
                     }
                     cout<<endl;
                 } cout<<endl<<endl<<endl;
                 for(int i=0; i<Wo.matrix.size(); i++)
                 {
                     for(int j=0; j<Wo.matrix[i].size(); j++)
                     {
                         cout<<Wo.matrix[i][j]<<" ";
                     }
                     cout<<endl<<endl;
                 }

        cout<<endl<<endl<<endl;
*/
        BackPropagationOp Object;

        Object.Wh=Wh;
        Object.Wo=Wo;

        while(Iterations<200)
        {
            Mse=0;
            Iterations++;
            vector<double> OutputsErros(n);
            vector<double> OutputsComErros(n);
            vector<double> HiddComErros(l);

            for(int d=0; d<k; d++)
            {
                Matrix inputs(m,1);
                Matrix outputs(n,1);
                for(int o=0; o<m; o++)
                {

                    inputs.matrix[o][0]=dataSet.matrix[d][o];
                }
                for(int o=0; o<n; o++)
                    outputs.matrix[o][0]=dataSet.matrix[d][o+m];





                Matrix netH(0,0);
                Matrix netO(0,0);

                for(int u=0; u<inputs.matrix.size(); u++)

                    inputs.matrix[u][0]=scale(inputs.matrix[u][0],maxmin[u].first,maxmin[u].second);
                for(int u=0; u<outputs.matrix.size(); u++)
                    outputs.matrix[u][0]=scale(outputs.matrix[u][0],maxmin[u+m].first,maxmin[u+m].second);

                Object.set( inputs, outputs, Object.Wh, Object.Wo,netH,netO,OutputsErros,OutputsComErros,HiddComErros,Bh,Bo);
                Object.Bh=Bh;
                Object.Bo=Bo;


                Object.ForwardPass();

                Object.ComOutError();
                Object.UpdateOutW();
                Object.ComHiddError();
                Object.UpdateHiddW();



                for(int i=0; i<OutputsErros.size(); i++)
                {
                    OutputsErros[i]+=(Object.OutputsErros[i]*Object.OutputsErros[i]);

                }

            }

            for(int i=0; i<OutputsErros.size(); i++)
            {
                OutputsErros[i]/=k;

            }
            Object.OutputsErros=OutputsErros;
            Mse=Object.ComputeMse();
            Object.ComComOutError();
            Object.UpdateOutW();
            Object.ComHiddError();
            Object.UpdateHiddW();


            if(Mse<BestMse)
            {
         //       cout<<Mse<<"   min  "<<tt<<endl;

                BestMse=Mse;

                BestWh=Object.Wh;
                BestWo=Object.Wo;
                BestBh=Object.Bh;
                BestBo=Object.Bo;

            }




        }
    }
// cout<<"/////////////////////////"<<endl;;
    cout<<BestWh.matrix.size()<<" "<<BestWh.matrix[0].size()<<endl;// dimension of WH
    for(int i=0; i<BestWh.matrix.size(); i++)
    {
        for(int j=0; j<BestWh.matrix[i].size(); j++)
        {
            cout<<BestWh.matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<BestWo.matrix.size()<<" "<<BestWo.matrix[0].size()<<endl;
    for(int i=0; i<BestWo.matrix.size(); i++)
    {
        for(int j=0; j<BestWo.matrix[i].size(); j++)
        {
            cout<<BestWo.matrix[i][j]<<" ";
        }
        cout<<endl;
    }




}

