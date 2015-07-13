
#include "rimage.h"
#include <stdexcept>
#include <fstream>
#define max(x,y)   x>y? x:y
#define min(x,y)   x<y? x:y

using std::cout;

//#define foralli for(int i=0; i<Vert(); i++ )
//#define forallj for(int j=0; j<Horz(); j++ )

rimage::rimage(int v, int h)
	: matrix(v, h)
{}

rimage::rimage(const rimage &r)
	: matrix(r)
{}

rimage & rimage::operator/=( int A )
{
	for(int i=0; i<Vert(); i++ )
		for(int j=0; j<Horz(); j++ )
			(*this)(i, j) /= A;
	//foralli forallj (*this)(i, j) /= A;
	return *this;
}

rimage operator+(const float& f, const rimage &r)
{
	rimage ans(r);
	ans += f;
	return ans;
}

rimage operator*(const rimage & R, const float &f)
{
	rimage ans(R);
	ans *= f;
	return ans;
}

rimage operator * (const rimage &r1, const rimage& r2)
{
	rimage ans(r1);
	ans *= r2;
	return ans;
}

rimage operator + (const rimage &r1, const rimage& r2)
{
	rimage ans(r1);
	ans += r2;
	return ans;
}


void rimage::UpsideDown( void )
{
	// Ok, this is less efficient than the old version, but it only happens on
	// loading, not in the iteration loop.
	int d2 = Vert()/2;
	for(int i=0; i<d2; i++ )
		//forallj std::swap((*this)(i,j), (*this)(Vert()-i-1,j));
		for(int j=0; j<Horz(); j++ )
			std::swap((*this)(i,j), (*this)(Vert()-i-1,j));
}

rimage rimage::Convolve(const rimage & Kern) const
{
	const int kvert = Kern.Vert(), khorz = Kern.Horz();
	const int dv = kvert / 2, dh = khorz / 2;

	rimage ans(Vert(), Horz());
	for(int i=0; i<Vert(); ++i) 
		for(int j=0; j<Horz(); ++j) {
			float sum = 0.0;	
			const int
				ik0 = i - dv,
				jl0 = j - dh,
				//kx0 = std::max(0, dh - i),
				// kx1 = std::min(khorz, Horz() + dh - i),
				//ky0 = std::max(0, dv - j),
				// ky1 = std::min(kvert, Vert() + dv - j);
				//adjusted by us
				kx0 = max(0, dh - i),
				kx1 = min(khorz, Horz() + dh - i),
				ky0 = max(0, dv - j),
				ky1 = min(kvert, Vert() + dv - j);

			for(int kx = kx0; kx < kx1; ++kx) {
				const int ik = ik0 + kx;

				for(int ky = ky0; ky < ky1; ++ky) {
					const int jl = jl0 + ky;

					sum += (*this)(ik, jl) * Kern(kx, ky);
				}
			}
			ans(i, j) = sum;
		}
		return ans;
}

rimage rimage::Convolve1(const rimage & Kern) const
{
	const int kvert = Kern.Vert(), khorz = Kern.Horz();
	const int dv = kvert / 2, dh = khorz / 2;

	rimage ans(Vert(), Horz());
	for(int i=0; i<Vert(); ++i){
		float sum = 0.0;
		for(int j=0; j<Horz(); ++j) {
			
		const int
			ik0 = i - dv,
			jl0 = j - dh,
			//kx0 = std::max(0, dh - i),
			// kx1 = std::min(khorz, Horz() + dh - i),
			//ky0 = std::max(0, dv - j),
			// ky1 = std::min(kvert, Vert() + dv - j);
			//adjusted by us
			kx0 = max(0, dh - i),
			kx1 = min(khorz, Horz() + dh - i),
			ky0 = max(0, dv - j),
			//preky0 = max(0, dv - (j-1)),
			ky1 = min(kvert, Vert() + dv - j);
		if(ky0 == 0 && ky1 == kvert){
			//if(0 == preky0){
			int jl = jl0 - 1 ;
			if(jl > -1)
				for(int kx = kx0; kx < kx1; ++kx) {
					const int ik = ik0 + kx;
					sum -= (*this)(ik, jl) * Kern(kx, 0);
				}
			//}

			//if(ky1 == kvert){
				jl = jl0 + kvert - 1;
				for(int kx = kx0; kx < kx1; ++kx) {
					const int ik = ik0 + kx;
					sum += (*this)(ik, jl) * Kern(kx, kvert - 1);
				}
			//}
		}else{
			sum = 0;
			for(int kx = kx0; kx < kx1; ++kx) {
				const int ik = ik0 + kx;

				for(int ky = ky0; ky < ky1; ++ky) {
					const int jl = jl0 + ky;

					sum += (*this)(ik, jl) * Kern(kx, ky);
				}
			}
		}
		
		ans(i, j) = sum;
	}
}
	return ans;
}


void rimage::SaveTarga( const char * name ) const
{
	int i,j;
	std::ofstream out(name, std::ios_base::binary|std::ios_base::out);
	if(!out) { cout << "Bad file name in rimage::SaveTarga\n"; exit(0);    }
	unsigned char ** A;
	A = new unsigned char *[Vert()];
	//foralli	A[i] = new unsigned char[Horz()];
	for( i=0; i<Vert(); i++ )
		A[i] = new unsigned char[Horz()];
	// Find max and min
	float max, min;
	max = Max();	min = Min();
	if( max == min )
		throw std::runtime_error("max == min in rimage::SaveTarga");

	// Determine gain and offset
	float gain, offset = min;
	gain = 255.0/ ( max - min );
	//foralli forallj A[i][j] = (unsigned char)( ( (*this)(i,j) - offset)*gain);
	for( i=0; i<Vert(); i++ )
		for( j=0; j<Horz(); j++ )
			A[i][j] = (unsigned char)( ( (*this)(i,j) - offset)*gain);

	out.write("\000\000\003\000\000\000\000\000\000\000\000", 12);

	unsigned short word = 0;
	word = Horz();  out.write((char*) &word, 2);
	word = Vert();  out.write((char*) &word, 2);
	// For some reason I don't understand, \008 gives a null char, but \b
	// works (gcc 3.4.2 on Fedora Core 3).
	out.write("\b\000", 2);

	for( i=Vert()-1; i>=0; i-- )	out.write((char*) A[i], Horz());
	//foralli	delete [] A[i];
	for( i=0; i<Vert(); i++ )
		delete [] A[i];
	delete [] A;
}
