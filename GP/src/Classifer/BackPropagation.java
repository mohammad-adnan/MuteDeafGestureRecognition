package Classifer;

import java.util.Vector;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author MohamedAtta
 */
public class BackPropagation {
        double LearningRate=.4;
    NeuralMatrix inputs;// just initialize size
    double Mse=0;
    NeuralMatrix outputs;// just initialize size
   NeuralMatrix Wh;
   NeuralMatrix Wo;
   // NeuralMatrix CurrentOutW;

    NeuralMatrix netH;
    NeuralMatrix netO;

    Vector<Double>OutputsErros;//outputs  error terms
    Vector<Double> OutputsComErros;// comulative error terms
    Vector<Double> HiddComErros;// comulative error terms

    void set(NeuralMatrix inputs,NeuralMatrix outputs,NeuralMatrix Wh,NeuralMatrix Wo,Vector<Double>OutputsErros,
                             Vector<Double>OutputsComErros,Vector<Double>HiddComErros)
{
    this.inputs=inputs;
    this.outputs=outputs;
    this.Wh=Wh;
    this.Wo=Wo;
    this.OutputsErros=(Vector<Double>) OutputsErros.clone();
  //  System.out.println("mohamed "+this.OutputsErros.size());

    this.OutputsComErros=OutputsComErros;

    this.HiddComErros=HiddComErros;
   // CurrentOutW=Wo;
}

    void  ForwardPass()
{

//compute neth
/*for(int i=0;i<inputs.matrix.size();i++)
{
for(int j=0;j<inputs.matrix.get(i).size();j++)
System.out.print(inputs.matrix.get(i).get(j)+" ");
System.out.print("\n");

}*/
    netH=Wh.mul(Wh,inputs);



// get f of net hidden

    netH=Fnet(netH);
//compute neto
    netO=Wo.mul(Wo,netH);
   netO=Fnet(netO);
}
    
    
    NeuralMatrix  Fnet(NeuralMatrix m)
{
    for(int i=0; i<m.matrix.length; i++)
        for(int j=0; j<m.matrix[i].length; j++)
        {
            
           float f=1/(1+(float) Math.exp(-1*m.matrix[i][j]));
            
         m.matrix[i][j]= f;
                           
        }

return m;

}

    // compute error term of outputs
void  ComOutError()
{
// error=actualoutputs-computesdoutputs;
//    cout<<endl<<" size "<<OutputsErros.size();
    for(int i=0; i<this.OutputsErros.size(); i++)
    {
      //  OutputsErros.setElementAt((double)outputs.matrix.get(i).get(0)-netO.matrix.get(i).get(0), i);

//cout<<outputs.matrix[i][0]<<"   "<<netO.matrix[i][0]<<endl;
    }
    // compute comulative error terms
    //comulative  output error=function of net outputerrorK *
    // function is derivative sigmoid function

}

double  ComputeMse()
{

    double mse=0;
    for(int i=0; i<OutputsErros.size(); i++)
        mse+=(OutputsErros.get(i)*OutputsErros.get(i));

	mse/=2;
   // CurrentOutW=(NeuralMatrix) Wo.matrix.clone();
    return mse;
}

    
    
}
