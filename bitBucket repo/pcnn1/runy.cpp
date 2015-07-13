#include"camera.h"
#include <time.h>
#include"neural/FeedForwardAlgorithm.h"
const int GestureNo = 1;
using namespace::std;
//char a[n][n];
#define n  100000000
int * a;
class Cla{
	public:
	int * a;
};
int get(int i){
	return a[i];
}

void set(int i, int v){
	a[i] = v;
}
int main()
{
	
	clock_t t1, t2 , t3;
	

	t1 = clock();
	vector<int> v(n);
	for(int i = 0 ;i < n;i++)
			v[i] = v[i] + 1;
	t2 = clock();
	cout <<"elapsed time:vector "<< (t2 - t1) / (double)(CLOCKS_PER_SEC)<<"\n" ;

	t1 = clock();
	Cla cla;
	a = new int[n];
	for(int i = 0 ;i < n;i++)
			set(i,get(i) + 1);
	t2 = clock();
	cout <<"elapsed time:array "<< (t2 - t1) / (double)(CLOCKS_PER_SEC)<<"\n" ;

	//time_t t1, t2 , t3;
	//Camera cam;
	//
	//FeedForwardAlgorithm instance;

	//
	//for(int i = 0 ;i < GestureNo; i++){
	//	cam.getGesture();
	//	//instance.run(cam.getGesture(),100);

	//}

	//t2 = time(0);
	//cout <<"elapsed time: "<< t2 - t1<<"\n" ;
	system("Pause");
    return 0;
}

