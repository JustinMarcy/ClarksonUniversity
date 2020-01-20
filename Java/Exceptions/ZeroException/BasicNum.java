public class BasicNum {
  //@ requires: ! (x==0 && y == 0)
  //@ signals_only: ZeroException (a user-defined, checked exception)
  //@ ensures: throws ZeroException if both x and y are zero,
  //@ otherwise returns the gcd of x and y.
  public static int gcd(int x, int y) throws ZeroException {
  }
          int gcd = 1;
          int a = x ;
          int b = y ;
          for(int i = 1; i <= a && i <= b; ++i)
          {
              if(a % i==0 && b % i==0)
                  gcd = i;
          }
          System.out.printf("Greatest common denominator of %d and %d is %d", a, b, gcd);
}
