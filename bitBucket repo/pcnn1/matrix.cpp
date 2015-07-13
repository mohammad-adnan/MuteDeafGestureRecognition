//
// matrix.cc
// jason Kinser
// 2 Feb 1995
// 15 October 1995
// 15 April 1996  Added == .
//

#include "matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

using std::cout;
using std::endl;
/*
#define foralli for(int i=0; i<vert; ++i)
#define forallj for(int j=0; j<horz; ++j)
*/
typedef unsigned char byte;

// ********* Begin matrix class

matrix::matrix( int d1, int d2 )
    : vert(d1), horz(d2),
      data(d1 * d2, 0)
{}

matrix::matrix( const matrix & A )
    : vert(A.vert), horz(A.horz),
      data(A.data.begin(), A.data.end())
{}

matrix::~matrix()
{}

//matrix& matrix::operator=( const matrix & b)
matrix& matrix::operator=( matrix & b)

{
   copy(b.data.begin(), b.data.end(), data.begin());
	//CopyBytes(b.data.begin(), b.data.end(), data.begin());
	//::matrix(b);
	//::data(b.data.begin(), b.data.end());
    return *this;
}

float matrix::Max() const
{
    std::vector<float>::const_iterator i = data.begin();
    float max = *i;
    while(++i != data.end())
	if(*i > max) max = *i;
    
    return max;
}

float matrix::Min() const
{
    std::vector<float>::const_iterator i = data.begin();
    float min = *i;
    while(++i != data.end())
	if(*i < min) min = *i;
    
    return min;
}

void matrix::Clear(const float A)
{
    for(std::vector<float>::iterator i = data.begin(); i != data.end(); ++i)
	*i = A;
}

matrix& matrix::operator *= (const float f)
{
    for(std::vector<float>::iterator i = data.begin(); i != data.end(); ++i)
	*i *= f;
    return *this;
}

matrix& matrix::operator += (const float f)
{
    for(std::vector<float>::iterator i = data.begin(); i != data.end(); ++i)
	*i += f;
    return *this;
}

matrix& matrix::operator *= (const matrix& m) {
    std::vector<float>::const_iterator b = m.data.begin();
    for(std::vector<float>::iterator a=data.begin(); a != data.end();
	++a, ++b)
	*a *= *b;
    return *this;
}

matrix& matrix::operator += (const matrix& m) {
    std::vector<float>::const_iterator b = m.data.begin();
    for(std::vector<float>::iterator a=data.begin(); a != data.end();
	++a, ++b)
	*a += *b;
    return *this;
}

bool matrix::operator == (const matrix& m){
	std::vector<float>::const_iterator b = m.data.begin();
    for(std::vector<float>::iterator a=data.begin(); a != data.end();++a, ++b)
		if(*a != *b)
			return false;

	return true;
}

float matrix::Sum( void ) const
{
    float sum = 0.0;
    for(std::vector<float>::const_iterator i = data.begin(); i != data.end();
	++i)
	sum += *i;
    
    return sum;
}

void matrix::Load (char *name)
{
    std::ifstream in(name);
    Load(in);
}

void matrix::Save (char *name)
{
    std::ofstream out(name);
    Save(out);
}

void matrix::Load(std::istream& in)
{
	int i,j;
    for(  i=0; i<vert; i++ ) for(  j=0; j<horz; j++ )
	in.read((char*) &(*this)(i, j), sizeof(float));
}

void matrix::Save(std::ostream& out)
{
	int i,j;
    for(  i=0; i<vert; i++ )  for(  j=0; j<horz; j++ )
	out.write((char*) &(*this)(i, j), sizeof(float));
}

// LoadByte
void matrix::LoadByte( char * name, int header )
{
	int i,j;
    std::ifstream in(name);
    if(!in) {
	cout << "Cannot open " << name << endl;
	exit(1); }
    
    char * head = new char[header];
   // in.read(head, header);
    delete head;
    
    byte ** A = new byte * [vert];
   // foralli A[i] = new byte[ horz ];
	for( i=0; i<Vert(); i++ )
		A[i] = new byte[ horz ];
	for( i=0; i<Vert(); i++ )
		in.read((char*)A[i], horz);
    
    /*foralli forallj {
	float t = A[i][j];
	(*this)(i, j) = t;
    }*/
	char  a[80];
	strcpy_s(a,name);strcat_s(a,".txt");
	ofstream o;
	o.open(a,ios::app);if(!o)  exit(0);
	for( i=0; i<Vert(); i++ ){
		for( j=0; j<horz; ++j)
		{
			float t = A[i][j];
			//cout <<i<<" "<<j<<":"<< t << " ";
			o<<(char)t;
			(*this)(i, j) = t;
		}
		//cout<<endl;
	}
	o.close();
		    //foralli delete A[i];

		for( i=0; i<Vert(); i++ )
			delete A[i];
    delete A;
}

void matrix::loadImage(Mat &m)
{
	int ii = Vert();
	int hh = m.rows;
	int i,j;
	for( i=0; i<Vert(); i++ ){
		for( j=0; j<Horz(); ++j)
		{
			//Vec3b data = m.at<Vec3b>(i,j);
			//data[0] = // blue pixel
			//data[1] = // green pixel
			//data[2] = // red pixel
			//cout <<"pixel:"<<  data[0] << " " <<  data[1] <<" " << data[2] << " " ;
			//cout<<"pixel:"<< (int)m.at<uchar>(i,j) <<endl;
			float t = (int)m.at<uchar>(i,j);
			(*this)(i, j) = t;
		}
	}
}