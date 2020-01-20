package intset;

public class IntSetTest {

  @Test
  public void test1() {
    IntSet r1 = new IntSet();
    assertTrue(r1.size() == 0);
  }

  @Test
  public void test2() {
    int[] ar2 = {34};
    IntSet r2 = new IntSet(ar2);
    int e = 34;
    r2.remove(e);
    assertTrue(r2.size() == 0);
  }

  @test
  public void test3() {
    int[] ar3 = {28, 34, -10, 12};
    IntSet r3 = new IntSet(ar3);
    assertTrue(ar3.isIn(28));
  }

  @test
  public void test4() {
    int[] ar4 = {1, 2, 3, 4};
    IntSet r4 = new IntSet(ar4);
    r4.insert(5);
    assertTrue(r4.size() > ar4.size());
  }

  @test
  public void test5() {
    int[] ar5 = {1};
    IntSet r5 = new IntSet(ar5);
    int result = r5.find(1);
    assertTrue(result == 0);
  }
}
