#include "matrix.h"

#ifndef RIMAGE
#define RIMAGE

typedef unsigned short word;
typedef unsigned long dword;

class rimage : public matrix {
public:
    rimage( int, int );
    rimage( const rimage & );
    rimage & operator/=( int );
// Math
    rimage Convolve(const rimage &) const;
// Image conversions
    void UpsideDown( void );
// Input / Output
    void SaveTarga( const char * ) const;
    
private:
    rimage( void );
    
};

rimage operator * (const rimage&, const float&);

inline  rimage operator * (const float& f, const rimage& i) {
    return i * f;
}

rimage operator + (const float& f, const rimage& i);

rimage operator + (const rimage& r1, const rimage& r2);
rimage operator * (const rimage& r1, const rimage& r2);

#endif


