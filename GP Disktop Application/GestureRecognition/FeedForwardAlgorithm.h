#include<vector>
#include<math.h>
#include <algorithm>
#include <string>
#include"BackPropagationOp.h"

using namespace std;
#ifndef algorithm
#define algorithm

class FeedForwardAlgorithm
{public:
double scale(double x,double xmin,double xmax);

 double descale(double x,double xmin,double xmax);
 int run(int *gesture,int size);

};
#endif
