import java.util.*;
import java.lang.Float;

public class TestExchange2 {
    public static void main(String[] args) {
	example1();
    }

    static void example1() {
	Float[] f1 = new Float[10];
	f1[0] = 4.567f;
	f1[1] = 45.76f;
	f1[2] = 0.435f;
	f1[3] = -21.8f;
	f1[4] = 123.2f;
	f1[5] = -34.5f;
	f1[6] = 23.67f;
	f1[7] = 8.675f;
	f1[8] = 87.90f;
	f1[9] = 31.02f;
	System.out.println(Arrays.toString(f1));
	UtilMethodGenerics.<Float>exchange(f1, 2, 9);
	System.out.println(Arrays.toString(f1));
    }
}
