package intset;


// tests remove
// tests intialization with duplicate values
import java.util.Arrays;

public class test3 {
    public static void main(String[] args) {
	int[] xar1 = new int[] {10, 67, 67, -10, 23, 58};

	IntSet tobj1 = new IntSet(xar1);
	System.out.println(tobj1);


	tobj1.remove(20);
	tobj1.remove(67);
	tobj1.insert(10);
	tobj1.insert(44);
	System.out.println(tobj1);	
    }

}
