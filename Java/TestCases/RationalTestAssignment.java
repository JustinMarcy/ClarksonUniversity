import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
    

/**
 * Tests Rational class.
 *
 * AbsFunc: a/b
 * Invariant: b != 0
 */
public class RationalTest {

    /**
     * Test default constructor of Rational
     * which assumes a = 0 and b = 1.
     */
    @Test
    public void test1() {
	Rational rat = new Rational();
		
	// check internal state of rat
	assertTrue(rat.getA() == 0);
	assertTrue(rat.getB() == 1);
    }

    /**
     * Test single argument constructor of Rational 
     * which specifies a and assumes b = 1.
     */
    @Test
    public void test2() {
	Rational rat = new Rational(7);
		
	// check internal state of rat
	assertTrue(rat.getA() == 7);
	assertTrue(rat.getB() == 1);
    }

    /**
     * Test two argument (primary) constructor of Rational 
     * which specifies a and b explicitly.
     */
    @Test
    public void test3() {
	Rational rat = new Rational(3, 4);
		
	// check internal state of rat
	assertTrue(rat.getA() == 3);
	assertTrue(rat.getB() == 4);
    }


   @Test
   public void test4() {
       Rational r1 = new Rational(3, -7);
       Rational r2 = new Rational(-3, 7);

       assertTrue(r1.isEqual(r2));
   }

   @Test
   public void test5() {
       Rational r1 = new Rational(-3, -7);
       Rational r2 = new Rational(3, 7);

       assertTrue("sign test", r1.isEqual(r2));
   }


   @Test
   public void test6() {
       Rational r1 = new Rational(-16, 24);

       assertEquals(r1, new Rational(-2, 3));
       assertEquals(r1, new Rational(2, -3)); //fails
       //assertEquals(r1, new Rational(-2, 5)); //fails
   }

   // @Test
   public void test7() {
       Rational r1 = new Rational(0, 24);
       Rational r2 = new Rational(0, -3);

       assertTrue("zero num test", r1.isEqual(r2));
   }


   @Test
   public void test8() {
       Rational r1 = new Rational(4, 11);
       Rational r2 = new Rational(-4, 11);

       assertFalse(r1.isEqual(r2));
   }
    

   @Test
   public void test9() {
       Rational r1 = new Rational(18, 7);
       Rational r2 = new Rational(7, 18);

       assertTrue(r1.isEqual(r2.recip()));
   }


   @Test
   public void test10() {
       Rational r1 = new Rational(0, 4);
       Rational r2 = new Rational(0, -4);

       assertTrue(r1.isEqual(r2));
   }



   @Test
   public void test11() {
       Rational r1 = new Rational(0, 4);
       Rational r2 = new Rational(-0, -4);

       assertTrue(r1.isEqual(r2));
   }
    
	
}
