
#include<string>
#include "PCNN.h"
#include <sstream>
#include<fstream>
#ifndef ImageSignature_H
#define ImageSignature_H
using namespace::std;
class ImageSignature{
public :
	string  gSignature;
	int start ; //position in signature array to add new partial image signature
	int sigLength; // signature array length 
	int numberofcutsitrs;
	int Niters ;
	int vert, horz;


	int* signature; // signature of a gesture (total signature of all images)
	ImageSignature(int frameNumber, int numberofcutsitrs, int Niters, int vert, int horz){
		this->numberofcutsitrs = numberofcutsitrs;
		this->Niters = Niters;
		this->vert = vert;
		this->horz = horz;
		sigLength = frameNumber * (Niters-numberofcutsitrs) ;
		signature = new int[sigLength];
		start = 0;
		 
		gSignature = "";
		
	}
	float** mat;
	ImageSignature(int frameNumber, int numberofcutsitrs, int Niters, int vert, int horz, float** mat){
		this->numberofcutsitrs = numberofcutsitrs;
		this->Niters = Niters;
		this->vert = vert;
		this->horz = horz;
		sigLength = frameNumber * (Niters-numberofcutsitrs) ;
		signature = new int[sigLength];
		start = 0;
		 
		gSignature = "";

		this->mat = mat;
	}
	// input path: path to image
	void getSignature(float** mat,int start2) {
		RImage *stim = new RImage(mat, vert, horz);
		// stim.LoadByte(path, 18 );
		// stim.loadImage(m);// I load it in constructor
		PCNN* Net = new PCNN(vert, horz);
		Net->vf = 0;
		stim->div(256);
		stim->upsideDown();
		for (int i = 0; i < Niters; i++) {
			int sum = Net->iterate(stim);// Net.FastIterate(stim);
			// cout << sum <<endl;
			if (i >= numberofcutsitrs) {
				signature[i + start2 - numberofcutsitrs] = sum;
				//sstream 
				//string ss =  " ";

				//gSignature += sum + ss;
			}
		}
		start += Niters - numberofcutsitrs;
	}
	void run() {
	//	getSignature(mat,0);
	}

	void save(){
		gSignature = "";
		for (int i = 0; i < 100; i++)
		{
			char * c = new char();

			gSignature += _itoa(signature[i], c, 10);
			gSignature += " ";
		}
		
		ofstream out("dataFile.data", ios::out | ios::app);
		if (!out) { out << "Bad file name in ImageSignature::save()\n"; exit(0); }
		//pack signatue to buffer
		//char * buffer = new char [sizeof(elementType) * sigLength];
		//memcpy(buffer, signature,sizeof(elementType) * sigLength);
		////write buffer to file 
		//out.write(buffer, sizeof(elementType) * sigLength);
		//out << signature <<endl;
		//cout <<"signature"<< signature;
		out << gSignature << " " << endl;
		/*	out << "array: ";
		for(int i = 0; i < sigLength ;i++){
		out << signature[i] << " ";
		}*/
		out << endl;

		out.close();
	}

};
#endif