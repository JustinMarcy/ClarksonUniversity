import java.util.Arrays;

public class TestExchange {
    public static void main(String[] args) {	
	example1();
	System.out.println();
	example2();
    }

    static void example1() {	
	Integer[] a1 = new Integer[5];
	a1[0] = 100;
	a1[1] = 40;
	a1[2] = 50;
	a1[3] = -10;
	a1[4] = 77;

	System.out.println(Arrays.toString(a1));
	UtilMethodGenerics.<Integer>exchange(a1, 1, 2);	
	//UtilMethodGenerics.exchange(a1, 1, 2); //works; the type argument can be inferred
	System.out.println(Arrays.toString(a1));
	
    }


    static void example2() {
	Double[] a1 = new Double[7];
	a1[0] = 100.0;
	a1[1] = -0.4;
	a1[2] = 5.9;
	a1[3] = -10.0;
	a1[4] = 7.88;
	a1[5] = 99.10;
	a1[6] = 88.0;

	System.out.println(Arrays.toString(a1));
	UtilMethodGenerics.<Double>exchange(a1, 0, a1.length-1);
	System.out.println(Arrays.toString(a1));	
    }
}
