package Classifer;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
//import javafx.util.Pair;

import org.opencv.pcnn.R;

import android.content.Context;
import android.util.Log;
import android.util.Pair;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author MohamedAtta
 */
public class FeedForward {

	double scale(double x, double xmin, double xmax) {

		if (xmax - xmin <= 0) {
			return 0;
		}

		double res = (x - xmin) / (xmax - xmin);
		if (res > 1) {
			return 1;
		} else if (res < 0) {
			return 0;
		} else {
			return res;
		}

	}

	double descale(double x, double xmin, double xmax) {

		return xmin + (x * (xmax - xmin));

	}

	public int run(Vector<Integer> gesture, int size, Context context)
			throws FileNotFoundException, IOException {
		int gestno = 0;
		Log.i("Neural", "PCNN run start");
		Scanner Reader = new Scanner(context.getResources().openRawResource(
				R.raw.weights));
		// FileWriter Writer = new FileWriter(new File("result.txt"));;

		// freopen("result.txt","w",stdout);
		int l, m, n, k, vecn;
		int minout, maxout;

		vecn = Reader.nextInt();
		// Writer.write("mohamed vecn ");
		// System.out.println(vecn);

		// Writer.write(String.valueOf(vecn));
		// Writer.write(" ");

		// Vector<Pair<Integer, Integer>> maxmin = new Vector();//vecn=n+n
		Vector<Pair<Integer, Integer>> maxmin = new Vector();// vecn=n+n
		maxmin.setSize(vecn);
		for (int h = 0; h < vecn; h++) {
			maxmin.set(h, new Pair(Reader.nextInt(), Reader.nextInt()));

		}

		l = Reader.nextInt();
		m = Reader.nextInt();
		// Writer.write(String.valueOf(l));
		// Writer.write(" ");
		//
		// Writer.write(String.valueOf(m));
		// Writer.write(" ");

		NeuralMatrix Wh = new NeuralMatrix(l, m);
		// cout<<"mohamed ijn feed forward";
		// for(;;);
		for (int i = 0; i < Wh.matrix.length; i++) {

			for (int j = 0; j < Wh.matrix[i].length; j++) {
				Wh.matrix[i][j] = Reader.nextFloat();// setElementAt(Reader.nextFloat(),
														// j);

			}

		}

		n = Reader.nextInt();
		l = Reader.nextInt();

		NeuralMatrix Wo = new NeuralMatrix(n, l);

		for (int i = 0; i < Wo.matrix.length; i++) {
			for (int j = 0; j < Wo.matrix[i].length; j++) {
				Wo.matrix[i][j] = Reader.nextFloat();// .setElementAt(Reader.nextFloat(),
														// j);
			}

		}

		minout = Reader.nextInt();
		maxout = Reader.nextInt();
		Log.i("Neural", "PCNN run end reading");
		// Writer.write(String.valueOf(minout));
		// Writer.write(" ");
		//
		// Writer.write(String.valueOf(maxout));
		// Writer.write(" ");

		BackPropagation object = new BackPropagation();

		// freopen("test.txt","r",stdin);
		// cin>>m>>l>>n>>k;
		k = 1;
		n = 1;
		m = size;

		// Writer.write("  Actual output     Excepected output");
		// Writer.write(" ");

		double Mse = 0;
		NeuralMatrix dataSet = new NeuralMatrix(k, m + n);
		for (int o = 0; o < m; o++) {
			// System.out.println("dataset "+o+"\n");
			dataSet.matrix[0][o] = (float) gesture.get(o);// .osetElementAt((float)gesture.get(o),o);

		}
		dataSet.matrix[0][0] = 00.0f;// .setElementAt(00.0f,0);

		/*
		 * for(int p=0; p<k; p++) { for(int h=0; h<m+n; h++) {
		 * 
		 * if(dataSet.matrix[p][h]>maxmin[h].second)
		 * maxmin[h].second=dataSet.matrix[p][h];
		 * if(dataSet.matrix[p][h]<maxmin[h].first)
		 * maxmin[h].first=dataSet.matrix[p][h];
		 * 
		 * 
		 * } }
		 */
		for (int p = 0; p < k; p++) {
			Vector<Double> OutputsErros = new Vector();
			OutputsErros.setSize(n);
			Vector<Double> OutputsComErros = new Vector();
			OutputsComErros.setSize(n);

			Vector<Double> HiddComErros = new Vector();
			HiddComErros.setSize(l);

			NeuralMatrix inputs = new NeuralMatrix(m, 1);
			NeuralMatrix outputs = new NeuralMatrix(n, 1);
			for (int o = 0; o < m; o++) {

				inputs.matrix[o][0] = dataSet.matrix[p][o];// .setElementAt(dataSet.matrix.get(p).get(o),
															// 0) ;
			}

			/*
			 * for(int o=0; o<n; o++) {
			 * outputs.matrix[o][0]=dataSet.matrix[p][o+m]; }
			 */
			for (int u = 0; u < inputs.matrix.length; u++) {
				for (int h = 0; h < inputs.matrix[u].length; h++) {
					inputs.matrix[u][h] = (float) scale(inputs.matrix[u][h],
							maxmin.get(u).first, maxmin.get(0).second);
					// cout << inputs.matrix[u][h]<<endl;
					// System.out.println(inputs.matrix.get(u).get(h));

				}
			}

			object.set(inputs, outputs, Wh, Wo, OutputsErros, OutputsComErros,
					HiddComErros);// second parameters Wh,Wo to run only
			Log.i("Neural", "PCNN run ForwardPass");
			object.ForwardPass();

			Log.i("Neural", "PCNN run descal");
			int gestn;
			for (int h = 0; h < object.netO.matrix.length; h++) {
				for (int yy = 0; yy < object.netO.matrix[h].length; yy++) {
					// Writer.write(String.valueOf(object.netO.matrix.get(h).get(yy)));
					// Writer.write("  nearest to ");

					object.netO.matrix[h][yy] = (float) descale(
							object.netO.matrix[h][yy], minout, maxout);
					gestno = Math.round(object.netO.matrix[h][yy]);
					// Writer.write(String.valueOf(gestno));

				}
			}

			// object.ComOutError();
			// Mse += object.ComputeMse();

		}
		Reader.close();
		// Writer.close();

		return gestno;

	}

}
