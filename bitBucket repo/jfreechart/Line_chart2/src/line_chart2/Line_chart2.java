/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package line_chart2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
import sun.org.mozilla.javascript.internal.ScriptRuntime;

/**
 *
 * @author Mohamed
 */
public class Line_chart2  {

   
    public Vector<Integer> readvector(String filename) throws FileNotFoundException {
        Vector<Integer> integers = new Vector<Integer>();
        Scanner fileScanner = new Scanner(new File(filename));
        while (fileScanner.hasNextInt()) {
            integers.add(fileScanner.nextInt());
        }
        return integers;
    }

    
    
    
    public static void main(String[] args) throws IOException {
      
      Line_chart2 obj = new Line_chart2();
       Vector<Integer> vec = new Vector<Integer>();
        vec=obj.readvector("test.txt");
        
      
        
        
        DefaultCategoryDataset line_chart_dataset = new DefaultCategoryDataset();
        for(int i=0;i<vec.size();i++){
        line_chart_dataset.addValue(vec.get(i), "Signature", Integer.toString(i));     
        }
        JFreeChart lineChartObject = ChartFactory.createLineChart(
                "Order Number Vs Signature", "Signature",
                "Order Number",
                line_chart_dataset, PlotOrientation.VERTICAL,
                true, true, false
        );
         
        
        int width = 640; // Width of the image  

        int height = 480;//  Height of the image 

        File lineChart = new File("LineChart.jpeg");
        ChartUtilities.saveChartAsJPEG(
                lineChart,
                lineChartObject,
                width, height
        );
        
    }

}
