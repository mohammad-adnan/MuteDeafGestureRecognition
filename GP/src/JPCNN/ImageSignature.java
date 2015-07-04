package JPCNN;


public class ImageSignature extends Thread{
	RImage ri;
	public String  gSignature;
	int start ; //position in signature array to add new partial image signature
	public int sigLength; // signature array length 
	int numberofcutsitrs;
	int Niters ;
	int vert, horz;
	

	public int[] signature; // signature of a gesture (total signature of all images)
	public ImageSignature(int frameNumber, int numberofcutsitrs, int Niters, int vert, int horz){
		this.numberofcutsitrs = numberofcutsitrs;
		this.Niters = Niters;
		this.vert = vert;
		this.horz = horz;
		sigLength = frameNumber * (Niters-numberofcutsitrs) ;
		signature = new int[sigLength];
		start = 0;
		 
		gSignature = "";
		
	}
	float[][] mat;
	public ImageSignature(int frameNumber, int numberofcutsitrs, int Niters, int vert, int horz, float[][] mat){
		this(frameNumber, numberofcutsitrs, Niters, vert, horz);
		this.mat = mat;
	}
	// input path: path to image
	public void getSignature(float[][] mat) {
		RImage stim = new RImage(mat, vert, horz);
		// stim.LoadByte(path, 18 );
		// stim.loadImage(m);// I load it in constructor
		PCNN Net = new PCNN(vert, horz);
		Net.vf = 0;
		stim.div(256);
		stim.upsideDown();
		for (int i = 0; i < Niters; i++) {
			int sum = Net.iterate(stim);// Net.FastIterate(stim);
			// cout << sum <<endl;
			if (i >= numberofcutsitrs) {
				signature[i + start - numberofcutsitrs] = sum;
				gSignature += sum + " ";
			}
		}
		start += Niters - numberofcutsitrs;
	}
	@Override
	public void run() {
		getSignature(mat);
	}
}
