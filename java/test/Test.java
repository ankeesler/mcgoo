// Test file for Mcgoo java.

package test;

import mcgoo.*;

import java.util.*;

public class Test extends McgooTest {

  public static void main(String[] args) { new Test(); }

  public Test() {
    add(new McgooCase() {
        public String name() { return "basicTest"; }
        public void run() {

          expect(true);

        }
      });
      
    failPolicy = FailPolicy.FINISH_TEST;
    add(new McgooCase() {
        public String name() { return "equalsTest"; }
        public void run() {
          
          List<Integer> list1 = new ArrayList<Integer>();
          expect(list1, list1);
          
          List<Integer> list2 = new ArrayList<Integer>();
          list1.add(1); list2.add(1);
          expect(list1, list2);
          
          List<Integer> list3 = new ArrayList<Integer>();
          nexpect(list1, list3);
          
          note("list1", list1);

          // Fail.
          expect(list1, list3);

        }
      });
      
    add(new McgooCase() {
        public String name() { return "failedTest"; }
        public void run() {
        
          expect(true);
          expect(true);
          expect(true);
          expect(false);
          expect(true);
          expect(true);
          expect(true);

        }
      });

    run();
  }
}

