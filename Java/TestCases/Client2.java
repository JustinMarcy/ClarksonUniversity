package intset;

public class Client2 {
    public static void main(String[] args) {
	int x[] =  {10, 100, 5, 3, 0, -30, 5};
	//IntSet is1 = getElements(x);

	IntSet is1 = new IntSet();
	is1.insert(3);
	is1.insert(4);
	is1.insert(4);
	is1.insert(-20);
	is1.insert(100);
	is1.insert(-2);
	is1.insert(34);
	is1.insert(400);
	System.out.println("invariant check: " + is1.repOK());

	System.out.println(is1.toString());
	is1.remove(4);
	is1.remove(99);
	is1.insert(99);

	is1.insert(0);
	System.out.println("invariant check: " + is1.repOK());
	is1.insert(222);
	is1.insert(124);	
	is1.insert(662);
	is1.insert(777);
	is1.insert(-1);	
	is1.insert(1000);
	is1.insert(76);
	is1.insert(1776);	
	is1.insert(1947);
	//is1.insert(662); //dupl entry
	System.out.println("invariant check: " + is1.repOK());
	
	System.out.println(is1.toString());

	System.out.println("invariant check: " + is1.repOK());
	
	is1.insert(1949);
	is1.insert(33);

	System.out.println("invariant check: " + is1.repOK());
		

	System.out.println("size of is1: " + is1.size());
	System.out.println("is1: " + is1);

	System.out.println("\n\nSelecting some element from intset is1");
	System.out.println(is1.choose());
	System.out.println(is1.choose());
	System.out.println(is1.choose());
	System.out.println(is1.choose());
	System.out.println(is1.choose());
	System.out.println("invariant check: " + is1.repOK());
		
	System.out.println(is1.choose());
		
	    
    }

   /*@ normal_behavior
     @ requires a != null;
     @ ensures (* \result = an IntSet containing all elements inside array a *);
     @ also
     @ exceptional_behavior
     @ requires a == null ;
     @ signals (NullPointerException e) true;
     @ signals_only NullPointerException
   */
    public static IntSet getElements(int[] a) throws NullPointerException {
	IntSet s = new IntSet();

	for (int e: a)
	    s.insert(e);

	return s;
    }
}

