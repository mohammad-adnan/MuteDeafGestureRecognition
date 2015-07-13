
#include "pcnn2d.h"
#include <cmath>
#include <fstream>
void print(rimage &im);
using std::cout;

PCNN::PCNN( int V, int H )
    : vert(V), horz(H),
      F(V,H), L(V,H), U(V,H), T(V,H), Y(V,H), K(5,5),
      af(10.0), al(1.0), at(5.0), beta(0.1),
      vf(0.5), vl(0.5), vt(20.0)
{
    StdK();
	//set theta
	T.setTheta(0.1);
}

PCNN::PCNN( const PCNN & P )
    : vert(P.vert), horz(P.horz),
      F(P.F), L(P.L), U(P.U),
      T(P.T), Y(P.Y), K(P.K),
      af(P.af), al(P.al), at(P.at),
      beta(P.beta),
      vf(P.vf), vl(P.vl), vt(P.vt)
{}

PCNN::~PCNN()
{}

int PCNN::KernVert() const
// returns the vertical dimension of the kernel
{
    return K.Vert();
}

int PCNN::KernHorz() const
{
    return K.Horz();
}

void PCNN::StdK()
{
    int i, j, kv, kh;  float val;
    kv = K.Vert();    kh = K.Horz();
    for( i=0; i<kv; i++ ) for( j=0; j<kh; j++ ) {
	val = hypot( i-kv/2, j-kh/2 );
	if( val != 0.0 ) val = 1.0/val;
	else val = 1.0;
	K(i, j) = val;
    }
}

rimage PCNN::Quantized()
{
    int i,j;   rimage ans( vert, horz );
    rimage work( vert, horz ), k( 3,3 );
    k.Clear( 1.0 );    work = Y.Convolve( k );
    for( i=0; i<work.Vert(); i++ ) for( j=0; j<work.Horz(); j++ )
	if( work(i, j) > 1.0 ) ans(i, j) = 1.0;
	else ans(i, j) = 0.0;
    return ans;
}

int PCNN::Iterate(const rimage & A)
{
    rimage work = Y.Convolve( K );

    F *= exp( -1.0/af ); F += vf * work; F += A;
    L *= exp( -1.0/al ); L += vl * work;
    U = F * (1.0 + beta *  L);
    for( int i=0; i<vert; i++ ) for( int j=0; j<horz; j++ )
	Y(i, j) = (U(i, j) > T(i, j)) ? 1.0 : 0.0;
    
    T *= exp( -1.0/at ); T += vt * Y;
	
    return int( Y.Sum( ) );
}
void print(rimage &im){
	for(int i = 0 ;i < im.Vert();i++){
		for(int j = 0 ;j < im.Horz();j++){
			cout << im(i, j) << " ";
		}
		cout << "\n";
	}
}
int PCNN::FastIterate(const rimage & A)
{
    rimage work( F.Vert(), F.Horz() ), Q( F.Vert(), F.Horz());
    int n=0;
    if( vf != 0 ) work = Y.Convolve( K );
    F = exp( -1.0/af ) * F + vf  * work + A;
    Y.Clear();
    do {
	Q = Y;   n++;
	L = Quantized( );
	U = F * (1.0 + beta *  L);
	for( int i=0; i<vert; i++ ) for( int j=0; j<horz; j++ )
	    if( U(i, j) > T(i, j) )
		Y(i, j) = 1.0;
    }  while( ( Q + Y).Sum() > 1 && n < 5);
    T = exp( -1.0/at ) * T + vt * Y;
    return int( Y.Sum( ) );
}

void PCNN::Clear()
{
    F.Clear();   L.Clear();    U.Clear();
    T.Clear();   Y.Clear();
}

void PCNN::Save( char * name )
{
    std::ofstream out(name);
    out.write((char*) &vert, sizeof( int ));
    out.write((char*) &horz, sizeof( int ));
    F.Save(out);	L.Save(out);
    U.Save(out);	T.Save(out);
    Y.Save(out);	K.Save(out);
    out.write((char*) &af, sizeof(float));
    out.write((char*) &al, sizeof(float));
    out.write((char*) &at, sizeof(float));
    out.write((char*) &beta, sizeof(float));
    out.write((char*) &vf, sizeof(float));
    out.write((char*) &vl, sizeof(float));
    out.write((char*) &vt, sizeof(float));
}

void PCNN::Load( char * name )
{
    std::ifstream in(name);
    if(!in) {
	cout << "Could not open file in PCNN::Load(char*)\n";
	exit( 0 );
    }
    in.read((char*) &vert, sizeof(int));
    in.read((char*) &horz, sizeof(int));
    F.Load(in);	L.Load(in);
    U.Load(in);	T.Load(in);
    Y.Load(in);	K.Load(in);
    in.read((char*) &af, sizeof(float));
    in.read((char*) &al, sizeof(float));
    in.read((char*) &at, sizeof(float));
    in.read((char*) &beta, sizeof(float));
    in.read((char*) &vf, sizeof(float));
    in.read((char*) &vl, sizeof(float));
    in.read((char*) &vt, sizeof(float));
}
