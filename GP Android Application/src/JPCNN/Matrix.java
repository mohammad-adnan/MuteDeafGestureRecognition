package JPCNN;

public class Matrix {
	
	private float[][] data;
	private int vert,horz;
	Matrix(int vert, int horz){
		this.vert = vert;
		this.horz = horz;
		data = new float[vert][horz];
	}
	
	Matrix(int vert, int horz, float theta){
		this(vert, horz);
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] = theta;
	}
	Matrix(float[][] data, int vert, int horz){
		this.vert = vert;
		this.horz = horz;
		this.data = data;
	}
	Matrix(Matrix m) {
		vert = m.getVert();
		horz = m.getHorz();
		data = new float[vert][horz];
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] = m.get(i, j);
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
				max = Math.max(max, data[i][j]);
		return max;
	}
	
    float min(){
    	float min = data[0][0];
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				min = Math.min(min, data[i][j]);
		return min;
    }
    float sum(){
    	float sum = 0;
		for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				sum += data[i][j];
		return sum;
    }

    Matrix mul(float f){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] *= f;
    	return this;
    }
    
    Matrix add(float f){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] += f;
    	return this;
    }
    
    Matrix mul(Matrix m){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] *= m.get(i, j);
    	return this;
    }
    
    Matrix add(Matrix m){
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				data[i][j] += m.get(i, j);
    	return this;
    }
    
    @Override
	public boolean equals(Object obj) {
    	Matrix m = (Matrix) obj;
    	if(m== null || m.data.length != vert || m.data[0].length != horz)
    		return false;
    	
    	for(int i = 0 ;i < vert;++i)
			for(int j = 0 ;j < horz;++j)
				if(data[i][j] != m.get(i, j))
					return false;
    	return true;
    	
	}

	public int getVert() {
		return vert;
	}
	public int getHorz() {
		return horz;
	}
	public float[][] getData() {
		return data;
	}
}
