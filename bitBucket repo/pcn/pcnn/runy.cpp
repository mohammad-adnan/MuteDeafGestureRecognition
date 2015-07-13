#include <sstream>
#include "pcnn2d.h"

const int dim = 128;
const int Niters = 3500;

int main()
{
    rimage stim( dim, dim );
    PCNN Net ( dim, dim );
    Net.vf = 0;
    stim.LoadByte( "lena.tga", 18 );
    stim /= 256;
    stim.UpsideDown( );
    int i;
    for( i=0; i<Niters; i++ ) {
	Net.Iterate( stim );
	std::ostringstream name;
	name << "yout";
	if( i <=9 ) name << '0';
	name << i << ".pbm";
	if( Net.Y.Max( ) > Net.Y.Min() ) Net.Y.SaveTarga( name.str().c_str() );
    }
    return 0;
}
