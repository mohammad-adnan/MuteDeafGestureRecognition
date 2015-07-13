#include<vector>
#include<math.h>
#include <algorithm>
#include <string>
#include <time.h>
//#include <iostream>
#include <fstream>
//#include "ImageSignature.h"
#include"FeedForwardAlgorithm.h"
//using namespace std;

double FeedForwardAlgorithm:: scale(double x,double xmin,double xmax)
{
	if (xmax - xmin <= 0)
		return 0;
	double res = (x - xmin) / (xmax - xmin);
	if (res > 1)
               		  return 1;
 	else if (res < 0) return 0;
	else		      return res;

}


double FeedForwardAlgorithm:: descale(double x,double xmin,double xmax)
{

    return xmin+(x*(xmax-xmin));

}

int FeedForwardAlgorithm:: run(int * gesture,int size)
{
	int gestno = 0;
	ofstream cout("result.txt", ios::out | ios::app);
	

	freopen("weights.txt","r",stdin);
	
 // freopen("result.txt","w",stdout);
  

		int l,m,n,k,vecn;
    float minout,maxout;

	cin >> vecn;
	cout  << "mohamed vecn "<<vecn;
	vector<pair<double, double> >maxmin(vecn);//vecn=n+n
	for (int h = 0; h<vecn; h++)
	{
		cin >> maxmin[h].first >> maxmin[h].second;

	}

    cin>>l>>m;
    cout<<l<<"  "<<m<<endl;
	
	NeuralMatrix Wh(l,m);
//cout<<"mohamed ijn feed forward";	
   //for(;;);
for(int i=0; i<Wh.matrix.size(); i++)
         {

	for(int j=0; j<Wh.matrix[i].size(); j++)
        {
            cin>>Wh.matrix[i][j];
        }

    }

	   cin>>n>>l;
    
	NeuralMatrix Wo(n,l);

    for(int i=0; i<Wo.matrix.size(); i++)
    {
        for(int j=0; j<Wo.matrix[i].size(); j++)
        {
            cin>>Wo.matrix[i][j];
        }
    
    }


	cin>>minout>>maxout;
    cout<<minout<<"  "<<maxout<<endl;

    BackPropagationOp object;
           
	//freopen("test.txt","r",stdin);



    //    cin>>m>>l>>n>>k;


    
	k=1;
	n = 1;
	m=size;




    cout<< "  Actual output     Excepected output"<<endl;
    double Mse=0;
     NeuralMatrix dataSet(k,m+n);
	for(int o=0;o<m+n;o++)
	{
		dataSet.matrix[0][o]=gesture[o];
	}
	dataSet.matrix[0][m]=0;
	/*for(int p=0; p<k; p++)
    {
        for(int h=0; h<m+n; h++)
        {

            if(dataSet.matrix[p][h]>maxmin[h].second)
                maxmin[h].second=dataSet.matrix[p][h];
            if(dataSet.matrix[p][h]<maxmin[h].first)
                maxmin[h].first=dataSet.matrix[p][h];


        }
    }
	*/
    for(int p=0; p<k; p++)
    {
        vector<double> OutputsErros(n);
        vector<double> OutputsComErros(n);
        vector<double> HiddComErros(l);

         NeuralMatrix inputs(m,1);
         NeuralMatrix outputs(n,1);
        for(int o=0; o<m; o++)
        {

            inputs.matrix[o][0]=dataSet.matrix[p][o];
        }

			
       /* for(int o=0; o<n; o++)
        {
            outputs.matrix[o][0]=dataSet.matrix[p][o+m];
        }
		*/
		
        for(int u=0; u<inputs.matrix.size(); u++)
            for(int h=0; h<inputs.matrix[u].size(); h++)
            {

                inputs.matrix[u][h]=scale(inputs.matrix[u][h],maxmin[u].first,maxmin[u].second);
//				cout << inputs.matrix[u][h]<<endl;
            }
			
	
			object.set(inputs,outputs,Wh,Wo,OutputsErros,OutputsComErros,HiddComErros);// second parameters Wh,Wo to run only

        object.ForwardPass();
		int gestn;
        for(int h=0; h<object.netO.matrix.size(); h++)
            for(int yy=0; yy<object.netO.matrix[h].size(); yy++)
            {
			cout << object.netO.matrix[h][yy] << "  nearest to ";

		object.netO.matrix[h][yy]=descale(object.netO.matrix[h][yy],minout,maxout);
				 gestno=round(object.netO.matrix[h][yy]) ;
				 cout << gestno;
	


            }

			
        object.ComOutError();
        Mse+=object.ComputeMse();


    }


	
    cout<<" MSE NO "<<endl;
    cout<<Mse<<" no";
	return gestno;
   
}