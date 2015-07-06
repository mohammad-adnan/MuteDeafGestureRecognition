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
public class NeuralMatrix {
    //  Vector<Vector<Float> >matrix;
  
      float [][] matrix;
      
      
      public  NeuralMatrix(int row,int column)
       {
    	  matrix = new float[row][column];
         /*  matrix=new Vector();
       matrix.setSize(row);
         for(int i=0; i<row; i++)
         {
             matrix.set(i,new Vector());
             matrix.get(i).setSize(column);

         }*/
         
       }

       
       void SetMatrixDim(int row,int column)
       {
    	   matrix = new float[row][column];
    	   /*
          matrix=new Vector();
       matrix.setSize(row);
         for(int i=0; i<row; i++)
         {
             matrix.set(i,new Vector());
             matrix.get(i).setSize(column);
       
         }*/
       
       }
// matrix multiplicatiion
    NeuralMatrix mul(NeuralMatrix mat1,NeuralMatrix mat2)
    {
    int row = mat1.matrix.length;
    int col = mat2.matrix[0].length;
     NeuralMatrix newMat=new NeuralMatrix(row,col);// 1 constant because the column size of input 1 forever

        for(int i=0; i<row; i++)
        {
            for(int j=0; j<newMat.matrix[i].length; j++)
            {
                newMat.matrix[i][j]=0.0f;
                for(int k=0; k<mat1.matrix[i].length; k++)
                {
                newMat.matrix[i][j] = newMat.matrix[i][j];
                }


            }
        }
return newMat;
    }
    // matrix addition
    NeuralMatrix add(NeuralMatrix mat1,NeuralMatrix mat2)
    {
     NeuralMatrix newMat=new NeuralMatrix(mat1.matrix.length,mat1.matrix[0].length);// 1 constant because the column size of input 1 forever
 for(int i=0; i<mat1.matrix.length; i++)
        {
            for(int j=0; j<mat1.matrix[i].length; j++)
            {

                 newMat.matrix[i][j] = mat1.matrix[i][j] +mat2.matrix[i][j];// setElementAt( mat1.matrix.get(i).get(j)+mat2.matrix.get(i).get(j);
           
            }
        }

        return newMat;
    }
    

}
