import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public class Writer {
    public static void write(ArrayList<IntersectionScheduled> scheduleds, String filename){
        try {
            String path = "C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\out\\" + filename + ".txt";
            FileWriter writer = new FileWriter(path);
            StringBuilder sb = new StringBuilder();

            //sb.append(scheduleds.size()).append("\n");

            int aux = 0;
            for (IntersectionScheduled intersectionScheduled: scheduleds) {
                Set<String> set = intersectionScheduled.schedule.keySet();
                if (set.size() == 0) continue;
                sb.append(intersectionScheduled.id).append("\n");
                sb.append(set.size()).append("\n");
                aux++;
                for (String name: set) {
                    sb.append(name).append(" ").append(intersectionScheduled.schedule.get(name)).append("\n");
                }
            }
            sb.insert(0, aux + "\n");
            writer.write(sb.toString());
            writer.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

    }
}
