package mcgoo;

import java.lang.Thread;

import java.util.*;

/** This class contains test utilities for java.
 *
 * Subclass this guy and let the testing begin.
 *
 * @author Andrew Keesler
 * @date January 10, 2015
 */
public class McgooTest {

  private List<McgooCase> testCases = new ArrayList<McgooCase>();

  private int expectNumber = 1;
  
  /** The choices of what action to take if an expect fails.
    */
  protected static enum FailPolicy {
    HARD_FAIL,
    FINISH_CASE,
    FINISH_TEST
  };
  
  /** What to do if a test fails.
    */
  protected FailPolicy failPolicy = FailPolicy.HARD_FAIL;
  
  private int failures = 0;

  /** Add a test case to be run.
   */
  public void add(McgooCase testCase) {
    testCases.add(testCase);
  }

  /** Run the test cases.
   */
  public void run() {
    long nanoTime;
    
    // Announce.
    System.out.printf("\n|*\n|* test : %s\n|*\n",
                      Thread.currentThread().getStackTrace()[2].getClassName());

    // Run.
    for (McgooCase testCase : testCases) {
      System.out.printf("(test = %s) [ ", testCase.name());
      nanoTime = System.nanoTime();
      testCase.run();
      nanoTime = System.nanoTime() - nanoTime; // rollover shmollover
      System.out.printf(" ] ( %.3f us ) %s\n",
                        nanoTime / 1000.0,
                        (((failPolicy == FailPolicy.FINISH_CASE)
                          && (failures > 0))
                         ? "FAIL"
                         : "PASS"));
    }

    // Summarize.
    System.out.printf("(TESTS : %d) (PASS : %d) (FAIL : %d)\n",
                       testCases.size(),
                       testCases.size() - failures,
                       failures);
  }
  
  /** Make a note in the test.
   */
  public void note(String variable, Object value) {
    System.out.printf("(%s=%s)", variable, value);
  }
  
  private void _expect(boolean thing, String failString) {
    int expectLine = Thread.currentThread().getStackTrace()[2].getLineNumber();
    
    if (thing) {
      System.out.print(".");
    } else {
      switch (failPolicy) {
      case HARD_FAIL:
        System.out.printf("X <- %d ] FAIL { %s } @ line %d\n",
                          expectNumber,
                          failString,
                          expectLine);
        System.exit(-1);
      case FINISH_CASE:
      case FINISH_TEST:
        System.out.printf("X(numb=%d, expt=%s, line=%d)",
                           expectNumber,
                           failString,
                           expectLine);
        failures ++;
        break;
      default:
        ; // this would totally never happen...
      }
    }

    expectNumber ++;
  }

  /** Expect that something is true.
   */
  public void expect(boolean thing) { _expect(thing, ""); }
  
  /** Expect that something is not true.
   */
  public void nexpect(boolean thing) { _expect(!thing, ""); }
  
  /** Expect that two things are equal.
   */
  public void expect(Object o1, Object o2) {
    _expect(o1.equals(o2),
            String.format("%s == %s", o1, o2));
  }
  
  /** Expect that two things are not equal.
   */
  public void nexpect(Object o1, Object o2) {
    _expect(!o1.equals(o2),
            String.format("%s != %s", o1, o2));
  }
}