package intset;

import java.util.Iterator;
import java.util.Arrays;

public class drv1 {
    public static void main(String[] args) {
	int[] ar1 = new int[] {921, -100, 11, 0, 21};

	IntSet s1  = new IntSet(ar1);
	System.out.println(s1);


	s1.remove(3);
	s1.remove(77);
	s1.insert(100);
	System.out.println(s1);

	
	System.out.println("\n\nTesting IntSet's iterator:");
	for (Iterator<Integer> it = s1.iterator(); it.hasNext();){
	    System.out.print(it.next() + " ");
	}
	System.out.println();


	//testing foreach loop with iterator
	System.out.println("\nTesting foreach loop with IntSets:");
	for (Integer e: s1) {
	    System.out.print(e + " ");
	}
	System.out.println();

    }

}

