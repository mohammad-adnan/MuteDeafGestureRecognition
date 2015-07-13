#include<math.h>
#include<cmath>
#include <algorithm> 
#ifndef Matrix_H
#define Matrix_H
using namespace::std;
class Matrix {
public:
	float **data;
	int vert,horz;
	Matrix(int vert, int horz){
		this->vert = vert;
		this->horz = horz;
		createMat(data,vert,horz);

			
	}
	void createMat(float ** &mat,int v,int h){
		mat = new float *[v];
		for(int i = 0 ;i < v;++i)
			mat[i] = new float[h];
		for(int i = 0 ;i < v;++i)
			for(int j = 0 ;j < h;++j)
				mat[i][j] = 0;

	}
	Matrix(int vert, int horz, float theta){
		this->vert = vert;
		this->horz = horz;
		data = new float *[vert];
		for(int i = 0 ;i < vert;++i)
			data[i] = new float[horz];

		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] = theta;
	}
	Matrix(float** data, int vert, int horz){
		this->vert = vert;
		this->horz = horz;
		this->data = data;
	}

	int getVert() {
		return vert;
	}
	 int getHorz() {
		return horz;
	}
	 float** getData() {
		return data;
	}
	Matrix(Matrix* m) {
		vert = m->getVert();
		horz = m->getHorz();
		createMat(data,vert,horz);
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] = m->get(i, j);
	}
	float get(int i, int j){
		return data[i][j];
	}
	
	void set(int i, int j, float f){
		data[i][j] = f;
	}
	float max(){
		float max = data[0][0];
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				max = std::max(max, data[i][j]);
		return max;
	}
	
    float min(){
    	float min = data[0][0];
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				min =  std::min(min, data[i][j]);
		return min;
    }
    float sum(){
    	float sum = 0;
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				sum += data[i][j];
		return sum;
    }

    Matrix* mul(float f){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] *= f;
    	return this;
    }
    
    Matrix* add(float f){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] += f;
    	return this;
    }
    
    Matrix* mul(Matrix m){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] *= m.get(i, j);
    	return this;
    }
    
    Matrix* add(Matrix m){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] += m.get(i, j);
    	return this;
    }
    

/*	public boolean equals(Object obj) {
    	Matrix m = (Matrix) obj;
    	if(m== null || m.data.length != vert || m.data[0].length != horz)
    		return false;
    	
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				if(data[i][j] != m.get(i, j))
					return false;
    	return true;
    	
	}*/

	 
};
#endif