/*
 * Exec: execute shell script - Test
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-10-28
 */

package util;

public class ExecTest {
    public static void main(String[] args) {
        try {
            String dir = "./src/util";  // Current working directory: `.` is project root directory

            // Test 1: Run shell script files
            Exec.$(dir, "echo [Test 1: Run shell script files]");
            {
                Exec.$(dir, "chmod 755 ./run_*");
                Exec.$(dir, "./run_1");
                Exec.$(dir, "./run_2");
            }
            Exec.$(dir, "echo");

            // Test 2: Run commands
            Exec.$(dir, "echo [Test 2: Run commands]");
            {
                Exec.$(dir, "sleep 3");
                Exec.$(dir, "printf \"Hello, \" > foo.txt");
                Exec.$(dir, "echo World! >> foo.txt");
                Exec.$(dir, "cat < foo.txt");
                Exec.$(dir, "rm foo.txt");
            }
            Exec.$(dir, "echo");

            // Test 3: Change working directory
            Exec.$(dir, "echo [Test 3: Change working directory]");
            {
                Exec.$(dir, "ls");
                Exec.$(dir, "echo");
                Exec.$("~", "ls");
            }
            Exec.$(dir, "echo");

            // Test 4: Communicate between stdin and stdout
            Exec.$(dir, "echo [Test 4: Communicate between stdin and stdout]");
            {
                Exec.$(dir, "cat");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}