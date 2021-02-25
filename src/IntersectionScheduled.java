import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class IntersectionScheduled {
    public int id;
    public HashMap<String, Integer> schedule;

    public IntersectionScheduled(int id) {
        this.id = id;
        this.schedule = new HashMap<>();
    }
}
