import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecWithOutput {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"python3", "-c", "import os; print('#',os.popen('java main.java').read())"});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("exitcode: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
