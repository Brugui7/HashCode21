import java.util.ArrayList;
import java.util.HashMap;

public
class Main {
    public static int MAX_INGREDIENTS = 10000;


    public static void main(String[] args) {

    }


}

class Pizza {
    int index;
    private boolean[] ingredientsArray;

    public Pizza(int index) {
        this.index = index;
        ingredientsArray = new boolean[Main.MAX_INGREDIENTS];
    }

    boolean compare(Pizza that){
        return that.ingredientsArray.length == this.ingredientsArray.length ? that.index < this.index : that.ingredientsArray.length > this.ingredientsArray.length;
    }
}

class PizzaDB {
    int pizzaIndex = 0;
    HashMap<String, Integer> ingredientsMap;
    ArrayList<Pizza> pizzas;

    void add(const )

}