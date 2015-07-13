package JPCNN;

public class RImage extends Matrix {

	public RImage(RImage r) {
		super(r);
		// TODO Auto-generated constructor stub
	}
	
	public RImage(int vert, int horz) {
		super(vert, horz);
		// TODO Auto-generated constructor stub
	}
	public RImage(float[][] data,int vert, int horz) {
		super(data, vert, horz);
		// TODO Auto-generated constructor stub
	}
	public RImage(int vert, int horz, float f) {
		super(vert, horz, f);
		// TODO Auto-generated constructor stub
	}
	
	RImage div(int a){
		for(int i = 0 ;i < getVert();++i)
			for(int j = 0 ;j < getHorz();++j)
				set(i, j, get(i, j) / a);
		return this;
	}
	
	static RImage add1(float f, RImage r){
		RImage ans = new RImage(r);
		ans.add(f);
		return ans;
	}
	
	static RImage mul1(float f, RImage r){
		RImage ans = new RImage(r);
		ans.mul(f);
		return ans;
	}
	
	static RImage add1( RImage r1, RImage r2){
		RImage ans = new RImage(r1);
		ans.add(r2);
		return ans;
	}
	
	static RImage mul1( RImage r1, RImage r2){
		RImage ans = new RImage(r1);
		ans.mul(r2);
		return ans;
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

	RImage convolve(RImage  Kern)
	{
		int kvert = Kern.getVert(), khorz = Kern.getHorz();
		int dv = kvert / 2, dh = khorz / 2;

		RImage ans = new RImage(getVert(), getHorz());
		for(int i=0; i<getVert(); ++i) 
			for(int j=0; j<getHorz(); ++j) {
				float sum = 0;	
				int
					ik0 = i - dv,
					jl0 = j - dh,
					kx0 = Math.max(0, dh - i),
					kx1 = Math.min(khorz, getHorz() + dh - i),
					ky0 = Math.max(0, dv - j),
					ky1 = Math.min(kvert, getVert() + dv - j);

				for(int kx = kx0; kx < kx1; ++kx) {
					int ik = ik0 + kx;

					for(int ky = ky0; ky < ky1; ++ky) {
						int jl = jl0 + ky;

						sum += this.get(ik, jl) * Kern.get(kx, ky);
					}
				}
				ans.set(i, j, sum);
			}
			return ans;
	}
}
