#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
    ifstream file ("warren.jpg", ifstream::binary);
    if(!file.is_open())
    {
        cout<<"can't open image";
        return 1;
    }
vector<vector<int> > binary;
int whitePixels = 0;
int height,width;
//we sholud read height and width

  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      if (binary[i][j] != 0)
        ++whitePixels;

    return 0;
}
