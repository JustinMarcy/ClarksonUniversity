package intset;


//client to demonstrate exposing of the rep (see IntSet.getAll());

//tests if  getAll exposes the rep or not


import java.util.Arrays;

public class test1 {
    public static void main(String[] args) {

	IntSet tobj1 = new IntSet();
	tobj1.insert(0);
	tobj1.insert(-10);
	tobj1.insert(5);
	tobj1.insert(0);
	tobj1.insert(1000);

	System.out.println(tobj1);
	
	//this call exposes the rep of IntSet
    	int[] contents_obj1 = tobj1.getAll();

    	System.out.println(Arrays.toString(contents_obj1));

    	for (int i = 0; i < contents_obj1.length; i++) {
    	    contents_obj1[i] = 0;
    	}

    	System.out.println(tobj1);
	
    }

}
