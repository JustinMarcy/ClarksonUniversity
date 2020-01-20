package intset;

import java.util.Arrays;

//a client for IntSet

public class Client1 {
    public static void main(String[] args) {
	IntSet s1 = new IntSet();

	s1.insert(30);
	s1.insert(-25);
	s1.insert(0);
	s1.insert(0);
	s1.insert(-1);

	
	System.out.println(s1);
	
	s1.remove(80);

	s1.remove(0);

	s1.remove(30);
	s1.insert(99);
	
	System.out.println(s1);


    }

}
