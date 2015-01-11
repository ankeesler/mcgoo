package mcgoo;

/** A test case.
 */
public interface McgooCase {

  /** Run the test case.
   */
  public void run();
  
  /** Return then name of the test case.
   */
  public String name();
}