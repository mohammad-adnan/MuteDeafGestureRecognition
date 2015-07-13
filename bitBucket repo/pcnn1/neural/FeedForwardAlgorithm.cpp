#include<vector>
#include<math.h>
#include <algorithm>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include"FeedForwardAlgorithm.h"
using namespace std;

double FeedForwardAlgorithm:: scale(double x,double xmin,double xmax)
{

    return (x-xmin)/(xmax-xmin);
}


double FeedForwardAlgorithm:: descale(double x,double xmin,double xmax)
{

    return xmin+(x*(xmax-xmin));
}

void FeedForwardAlgorithm:: run(int * gesture,int size)
{
	cout<<"testing";     	
   
	freopen("output.txt","r",stdin);
	
    freopen("result.txt","w",stdout);
      

		int l,m,n,k;
    float minout,maxout;
    cin>>l>>m;
/*    Matrix Wh(l,m);
    for(int i=0; i<Wh.matrix.size(); i++)
    {
        for(int j=0; j<Wh.matrix[i].size(); j++)
        {
            cin>>Wh.matrix[i][j];
        }

    }
    cin>>n>>l;
    Matrix Wo(n,l);

    for(int i=0; i<Wo.matrix.size(); i++)
    {
        for(int j=0; j<Wo.matrix[i].size(); j++)
        {
            cin>>Wo.matrix[i][j];
        }

    }
           cin>>minout>>maxout;


    BackPropagationOp object;
    //freopen("test.txt","r",stdin);


//    cin>>m>>l>>n>>k;




    vector<pair<double ,double> >maxmin(m+n);
    for(int i=0; i<maxmin.size(); i++)
    {
        maxmin[i].first=99999999;// any big number
        maxmin[i].second=0;

    }


    cout<< "  Actual output     Excepected output"<<endl;
    double Mse=0;
	k=1;
	n=1;
	m=size;
    Matrix dataSet(k,m+n);
	for(int o=0;o<size;o++)
	{
		dataSet.matrix[0][o]=gesture[o];
	}

	for(int p=0; p<k; p++)
    {
        for(int h=0; h<m+n; h++)
        {

            if(dataSet.matrix[p][h]>maxmin[h].second)
                maxmin[h].second=dataSet.matrix[p][h];
            if(dataSet.matrix[p][h]<maxmin[h].first)
                maxmin[h].first=dataSet.matrix[p][h];


        }
    }

    for(int p=0; p<k; p++)
    {
        vector<double> OutputsErros(n);
        vector<double> OutputsComErros(n);
        vector<double> HiddComErros(l);

        Matrix inputs(m,1);
        Matrix outputs(n,1);
        for(int o=0; o<m; o++)
        {

            inputs.matrix[o][0]=dataSet.matrix[p][o];
        }

        for(int o=0; o<n; o++)
        {
            outputs.matrix[o][0]=dataSet.matrix[p][o+m];
        }
        for(int u=0; u<inputs.matrix.size(); u++)
            for(int h=0; h<inputs.matrix[u].size(); h++)
            {

                inputs.matrix[u][h]=scale(inputs.matrix[u][h],maxmin[u].first,maxmin[u].second);
            }
        object.set(inputs,outputs,Wh,Wo,OutputsErros,OutputsComErros,HiddComErros);// second parameters Wh,Wo to run only

        object.ForwardPass();

        for(int h=0; h<object.netO.matrix.size(); h++)
            for(int yy=0; yy<object.netO.matrix[h].size(); yy++)
            {
                object.netO.matrix[h][yy]=descale(object.netO.matrix[h][yy],minout,maxout);
                cout<<object.netO.matrix[h][yy]<<"       "<<p<<"   ";
                cout<<object.outputs.matrix[h][yy]<<endl;


            }


        object.ComOutError();
        Mse+=object.ComputeMse();




    }



    cout<<" MSE "<<endl;
    cout<<Mse/k;



	*/
}

