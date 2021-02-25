import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Intersection {
    public int id;
    public List<Street> in, out;

    public Intersection(int id) {
        this.id = id;
        this.in = new ArrayList<>();
        this.out = new ArrayList<>();
    }
}
