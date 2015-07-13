#include "rimage.h"

class PCNN {
    int vert, horz;
    rimage Quantized();
public:
    rimage F, L, U, T, Y, K;
    float af, al, at, beta, vf, vl, vt;
    PCNN( int, int );	// The two dimensions
    PCNN( const PCNN & );	// copy
    ~PCNN();
    int KernVert() const;
    int KernHorz() const;
    void StdK();
    int Iterate(const rimage &);
    int FastIterate(const rimage &);   // uses fast linking
    void Clear();
    void Save(char *);
    void Load(char *);
};
