import java.util.*;
public class UtilMethodGenerics {

    public static void main(){

    }


    public static <T> void exchange(T[] arr, int p, int q) {
	T temp = arr[p];
	arr[p] = arr[q];
	arr[q] = temp;
    } 
}

//sources: https://stackoverflow.com/questions/13766209/effective-swapping-of-elements-of-an-array-in-java
