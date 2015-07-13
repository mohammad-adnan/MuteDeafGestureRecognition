
#include <vector>
#include <iostream>

#ifndef MATRIX
#define MATRIX

class matrix {
public:
// Memory management
    matrix( int, int );
    matrix( const matrix & );
    ~matrix( void );
    
    const float& operator() (const int i, const int j) const;
    float& operator() (const int i, const int j);
// Simple Math
    //matrix & operator=( const matrix & );
	matrix & operator=(  matrix & );
// Information
    int Vert() const { return vert; }
    int Horz() const { return horz; }
    
    float Max() const;
    float Min() const;
    float Sum() const;
    
// Per-element operations    
    void Clear(const float = 0);
    matrix& operator *= (const float f);
    matrix& operator += (const float f);

    matrix& operator *= (const matrix& m);
    matrix& operator += (const matrix& m);
    
// IO
    void Save (char *name);
    void Load (char *name);
    void Save(std::ostream&);
    void Load(std::istream&);
    void LoadByte( char *, int );
    
private:
    matrix();
    
    int vert, horz;
    std::vector<float> data;
};

inline const float& matrix::operator()(const int i, const int j) const
{
    return data[i*horz + j];
}
inline float& matrix::operator()(const int i, const int j)
{
    return data[i*horz + j];
}


#endif
