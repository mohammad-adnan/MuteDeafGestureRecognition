package JPCNN;

public class PCNN {
	private int vert, horz;
	RImage F, L, U, T, Y, K;
    float af, al, at, beta, vf, vl, vt;
    PCNN(int v, int h){	// The two dimensions
    	vert = v;
    	horz = h;
    	F = new RImage(v, h);
    	L = new RImage(v, h);
    	U = new RImage(v, h);
    	T = new RImage(v, h);
    	Y = new RImage(v, h);
    	K = new RImage(5, 5);
    	af = (float) (10.0); al = (float) (1.0); at = (float) (5.0); beta = (float) (0.1);
        vf = (float) (0.5); vl = (float) (0.5); vt = (float) (20.0);
        
        stdK();
        
        //set theta
    	T = new RImage(v, h, (float) 0.1);
    	
    }
	void stdK() {
		int i, j, kv, kh;
		float val;
		kv = K.getVert();
		kh = K.getHorz();
		for (i = 0; i < kv; i++)
			for (j = 0; j < kh; j++) {
				val = (float) Math.hypot(i - kv / 2, j - kh / 2);
				if (val != 0.0)
					val = (float) (1.0 / val);
				else
					val = (float) 1.0;
				K.set(i, j, val);
			}
	}

	int iterate(RImage A) {
		RImage work = Y.convolve(K);

		F.mul((float) Math.exp(-1.0 / af));
		F.add(RImage.mul1(vf, work));
		F.add(A);
		L.mul((float) Math.exp(-1.0 / al));
		L.add(RImage.mul1(vl, work));
		U = new RImage(RImage.mul1(beta, L).add((float) 1.0).mul(F).getData(),vert,horz);
		for (int i = 0; i < vert; i++)
			for (int j = 0; j < horz; j++)
				Y.set(i, j, (float) (((U.get(i, j) > T.get(i, j)) ? 1.0 : 0.0)));

		T.mul((float) Math.exp(-1.0 / at));
		T.add(RImage.mul1(vt, Y));

		return (int) Y.sum();
	}
}
