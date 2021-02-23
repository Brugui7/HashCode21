import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public class Writer {
    public static void write(ArrayList<ArrayList<Integer>> delivering, String filename){
        try {
            String path = "C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\out\\" + filename + ".txt";
            File myObj = new File(path);
            FileWriter writer = new FileWriter(path);
            StringBuilder sb = new StringBuilder();

            sb.append(delivering.size()).append("\n");
            for (ArrayList<Integer> deliver: delivering) {
                sb.append(deliver.size());
                for (int pizzaIndex: deliver) {
                    sb.append(" ").append(pizzaIndex);
                }
                sb.append("\n");
            }
            writer.write(sb.toString());
            writer.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

    }
}
