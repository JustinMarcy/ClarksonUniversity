package intset;


//client to demonstrate possible exposing of the rep

//one of the  "IntSet(int[] sarr)" constructors exposes the rep (see IntSet.java)

import java.util.Arrays;

public class test2 {
    public static void main(String[] args) {

	int[] inarr = {2, 4, 100, -40};
	IntSet tobj2 = new IntSet(inarr);

	System.out.println(tobj2);
    	System.out.println(Arrays.toString(inarr));


	System.out.println("\n\nmain: modifying array inarr");
	for (int i = 0; i < inarr.length; i++) {
	    inarr[i] = -10;
	}

	System.out.println(tobj2);
    }

}
