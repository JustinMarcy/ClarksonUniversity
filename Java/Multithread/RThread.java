//import java.lang.Runnable;
//import java.lang.String;
//import java.lang.Math;
import java.util.*;

public class RThread implements Runnable{
    String name;
    int L;
    int R;

    RThread(String label, int left,int right){
    	name = label;
    	L = left;
    	R = right;

    }
    public void run() {
	double sum=0; 
	for (int i=L; i<=R; i++) {
	    sum = sum + Math.sqrt(i);
	}
	double avg=sum/(R-L+1);
	System.out.println("["+name+"]: "+"Average of Square Roots ("+L+","+R+") = " + avg);
    }
}
