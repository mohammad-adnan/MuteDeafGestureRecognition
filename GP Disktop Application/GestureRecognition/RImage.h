
#include "Matrix.h"
#ifndef RImage_H
#define RImage_H
class RImage :public Matrix {

 public:
	RImage(RImage *r):Matrix(r) {
		// TODO Auto-generated constructor stub
	}
	
	RImage(int vert, int horz):Matrix(vert, horz){
		
		// TODO Auto-generated constructor stub
	}
	  RImage(float ** data,int vert, int horz) :Matrix(data, vert, horz){
		// TODO Auto-generated constructor stub
	}
	  RImage(int vert, int horz, float f):Matrix(vert, horz, f) {
		
		// TODO Auto-generated constructor stub
	}
	
	RImage* div(int a){
		for(int i = 0 ;i < getVert();++i)
			for(int j = 0 ;j < getHorz();++j)
				set(i, j, get(i, j) / a);
		return this;
	}
	
	void upsideDown() {
		int d2 = getVert() / 2;
		for (int i = 0; i < d2; ++i)
			for (int j = 0; j < getHorz(); ++j) {
				float temp = get(i, j);
				set(i, j, get(getVert() - i - 1, j));
				set(getVert() - i - 1, j, temp);
			}
	}

	RImage* convolve(RImage*  Kern)
	{
		int kvert = Kern->getVert(), khorz = Kern->getHorz();
		int dv = kvert / 2, dh = khorz / 2;

		RImage* ans = new RImage(getVert(), getHorz());
		for(int i=0; i<getVert(); ++i) 
			for(int j=0; j<getHorz(); ++j) {
				float sum = 0;	
				int
					ik0 = i - dv,
					jl0 = j - dh,
					kx0 = std::max(0, dh - i),
					kx1 = std::min(khorz, getHorz() + dh - i),
					ky0 = std::max(0, dv - j),
					ky1 = std::min(kvert, getVert() + dv - j);

				for(int kx = kx0; kx < kx1; ++kx) {
					int ik = ik0 + kx;

					for(int ky = ky0; ky < ky1; ++ky) {
						int jl = jl0 + ky;

						sum += this->get(ik, jl) * Kern->get(kx, ky);
					}
				}
				ans->set(i, j, sum);
			}
			return ans;
	}
};


	RImage* add1(float f, RImage *r){
		RImage* ans = new RImage(r);
		ans->add(f);
		return ans;
	}
	
	RImage* mul1(float f, RImage *r){
		RImage * ans = new RImage(r);
		ans->mul(f);
		return ans;
	}
	
	RImage* add1( RImage *r1, RImage* r2){
		RImage* ans = new RImage(r1);
		ans->add(r2);
		return ans;
	}
	
	RImage* mul1( RImage *r1, RImage *r2){
		RImage* ans = new RImage(r1);
		ans->mul(r2);
		return ans;
	}
#endif