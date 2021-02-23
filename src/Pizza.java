import java.util.ArrayList;

public class Pizza {
    int index;
    public ArrayList<String> ingredientsArray;

    public Pizza(int index,  ArrayList<String> ingredientsArray) {
        this.index = index;
        this.ingredientsArray = ingredientsArray;
    }

    public Pizza() {
        this.ingredientsArray = new ArrayList<>();

    }

    boolean compare(Pizza that){
        return that.ingredientsArray.size() == this.ingredientsArray.size() ? that.index < this.index : that.ingredientsArray.size() > this.ingredientsArray.size();
    }
}