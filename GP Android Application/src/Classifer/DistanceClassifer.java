package Classifer;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;

import org.opencv.pcnn.R;

import android.content.Context;

public class DistanceClassifer extends Thread {

    Vector<Vector<Double>> avgsignatures;

    public DistanceClassifer(Context context) throws FileNotFoundException {
        avgsignatures = new Vector<Vector<Double>>();

        //File file = new File("weights.txt");
        Scanner scan = new Scanner(context.getResources().openRawResource(R.raw.weights));
        while (scan.hasNext()) {
            String avgsignature = scan.nextLine();
            String tokens[] = avgsignature.split(" ");
            Vector<Double> avg = new Vector<Double>();
            for (String token : tokens) {

                avg.add(Double.parseDouble(token));

            }
            this.avgsignatures.add(avg);
        }
        
        scan.close();
    

    }

    
    //this method take input signatiure
    //return -1 if there is an error
    //return >=0 distance 
    
   public int calculateDistances(Vector<Integer> inputSignature){
	   
	   if(inputSignature.size()!= avgsignatures.get(0).size()){
		   return -1;
	   }
	   int output;
	  Vector<Double>distances = new Vector<Double>();
	   Vector<Double>tempDistance ;
	   double difrence=0;
	   double sum=0;
	   for(int i=0;i<avgsignatures.size();i++){
		   tempDistance = new Vector<Double>();
		   
		   for(int j=0;j<avgsignatures.get(i).size();j++){
			  difrence = avgsignatures.get(i).get(j) -  inputSignature.get(j);
			  tempDistance.add(difrence);		   
		   }
	   
		   
		   for(int j=0;j<tempDistance.size();j++){
			  sum+=(tempDistance.get(j)*tempDistance.get(j));
			   
		   }
		   distances.add(sum);
		   sum=0;
	   }
	  
	   output = getmin(distances);
	   return output+1;
	   
	   
   }
    
    
    
    
    
    public int getmin(Vector<Double> distances){
    	int min=0;
    	
    	for(int i=1;i<distances.size();i++){
    		if(distances.get(i)<distances.get(min)){
    			
    			min=i;
    		}
    		    		   		
    	}
    	
    	return min;	
    }
    
    
    
    
    
    
    
}
