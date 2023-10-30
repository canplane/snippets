/*
 * Exec: execute shell script
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-10-28
 */

package util;

import java.io.File;
import java.io.IOException;

public class Exec {
    private static final String $SHELL = "/bin/bash";
    private static final String $HOME = System.getProperty("user.home");

    public static int $(String dir, String command) throws IOException, InterruptedException {
        dir = resolvePath(dir);

        // option -i added to read all environment variables in ~/.bashrc
        ProcessBuilder pb = new ProcessBuilder($SHELL, "-ic", command);
        pb.directory(new File(dir));
        pb.inheritIO();

        Process p = pb.start();
        p.waitFor();
        return p.exitValue();
    }
    public static String resolvePath(String path) {
        path = path.trim();
        if (path.startsWith("~")) {
            path = $HOME + path.substring(1);
        }
        return path;
    }
}