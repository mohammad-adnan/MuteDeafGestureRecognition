#include "ImageSignature.h"

ImageSignature::ImageSignature(int frameNumber):testRimage(dim,dim)
{
	sigLength = frameNumber * (Niters-numberofcutsitrs) ;
	signature = new elementType[sigLength];
	start = 0;
	 
	gSignature = "";
}


ImageSignature::~ImageSignature(void)
{
	delete [] signature;
}

//input path: path to image
void ImageSignature::getSignature(Mat &m)
{
	rimage stim( dim, dim );
	//stim.LoadByte(path, 18 );
	stim.loadImage(m);//I added this insted of LoadByte
    PCNN Net ( dim, dim );
    Net.vf = 0;
    stim /= 256;
    stim.UpsideDown( );
	if(testRimage == stim){
		cout << "YES OMG!";
	}else
		cout << "NO\n";
	testRimage = stim;
    int i;
    for( i=0; i<Niters; i++ ) {
		elementType sum =Net.Iterate( stim );//Net.FastIterate(stim);
		//cout << sum <<endl;
		if(i >=  numberofcutsitrs)
		{
		signature[i + start - numberofcutsitrs]= sum;
		//signature += sum + " ";
		//cout<<signature<<endl;
		char * c =new char();
		
		gSignature += _itoa(sum, c,10); 
		//delete c;
		gSignature += " ";
		}
		//cout <<"gSignature = "<< gSignature << endl;
    }
	start += Niters - numberofcutsitrs;
}

void ImageSignature::save(){
	ofstream out("dataFile.data", ios::out | ios::app);
	if(!out) { cout << "Bad file name in ImageSignature::save()\n"; exit(0);}
	//pack signatue to buffer
	//char * buffer = new char [sizeof(elementType) * sigLength];
	//memcpy(buffer, signature,sizeof(elementType) * sigLength);
	////write buffer to file 
	//out.write(buffer, sizeof(elementType) * sigLength);
	//out << signature <<endl;
	//cout <<"signature"<< signature;
	out <<"string: "<< gSignature << " " << endl;
	out << "array: ";
	for(int i = 0; i < sigLength ;i++){
		out << signature[i] << " ";
	}
	out <<endl;
	
	out.close();
}

void ImageSignature::readSignature(){
	//ifstream in("dataFile.data", ios::in | ios::binary);
	//if(!in) { cout << "Bad file name in ImageSignature::save()\n"; exit(0);}
	//char * buffer = new char [sizeof(elementType) * sigLength];
	//in.read(buffer, sizeof(elementType) * sigLength);
	////unpack buffer to signature
	//memcpy(signature, buffer, sizeof(elementType) * sigLength);
	//in.close();
}
