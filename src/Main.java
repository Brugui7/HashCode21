import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
/**
 * OBJETIVO: maximizar el número de ingredientes distintos por equipo
 */

/**
 * 1. Leer el archivo y mapear todos los ingredientes distintos
 * 1.1 Crear objetos pizza (index -> ID
 */
public
class Main {
    public static int MAX_INGREDIENTS = 10000;


    public static void main(String[] args) {
        //getDatasetsInfo();
        PizzaDB pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\a_example");
        pizzaDB.magic();
        Writer.write(pizzaDB.delivering, "a");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\b_little_bit_of_everything.in");
        pizzaDB.magic();
        Writer.write(pizzaDB.delivering, "b");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\c_many_ingredients.in");
        pizzaDB.magic();
        Writer.write(pizzaDB.delivering, "c");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\d_many_pizzas.in");
        pizzaDB.magic();
        Writer.write(pizzaDB.delivering, "d");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\e_many_teams.in");
        pizzaDB.magic();
        Writer.write(pizzaDB.delivering, "e");

    }

    private static void getDatasetsInfo() {
        System.out.println("\n\n######### DATASET A #########");
        Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\a_example");
        System.out.println("\n\n######### DATASET B ######### ");
        Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\b_little_bit_of_everything.in");
        System.out.println("\n\n######### DATASET C ######### ");
        Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\c_many_ingredients.in");
        System.out.println("\n\n######### DATASET D #########");
        Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\d_many_pizzas.in");
        System.out.println("\n\n######### DATASET E #########");
        Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\e_many_teams.in");
    }
}


class PizzaDB {
    int teamsOf2, teamsOf3, teamsOf4;
    public ArrayList<Pizza> pizzas;
    public ArrayList<ArrayList<Integer>> delivering;

    public PizzaDB(int teamsOf2, int teamsOf3, int teamsOf4, ArrayList<Pizza> pizzas) {
        this.teamsOf2 = teamsOf2;
        this.teamsOf3 = teamsOf3;
        this.teamsOf4 = teamsOf4;
        this.pizzas = pizzas;
        delivering = new ArrayList<>();
    }


    /**
     * LA MAGIA
     * Reparte las pizzas entre los equipos intentando maximizar el número de ingredientes distintos
     */
    void magic() {
        for (int i = 0; i < this.teamsOf4; i++) {
            if (pizzas.size() < 4) break;
            ArrayList<Integer> aux = new ArrayList<>();
            for (int j = 0; j < 4; j++) {
                aux.add(pizzas.get(j).index);
            }
            pizzas.remove(0);
            pizzas.remove(0);
            pizzas.remove(0);
            pizzas.remove(0);
            delivering.add(aux);
        }
        for (int i = 0; i < this.teamsOf3; i++) {
            if (pizzas.size() < 3) break;
            ArrayList<Integer> aux = new ArrayList<>();
            for (int j = 0; j < 3; j++) {
                aux.add(pizzas.get(j).index);
            }
            pizzas.remove(0);
            pizzas.remove(0);
            pizzas.remove(0);
            delivering.add(aux);

        }
        for (int i = 0; i < this.teamsOf2; i++) {
            if (pizzas.size() < 2) break;
            ArrayList<Integer> aux = new ArrayList<>();
            for (int j = 0; j < 2; j++) {
                aux.add(pizzas.get(j).index);
            }
            pizzas.remove(0);
            pizzas.remove(0);
            delivering.add(aux);

        }
    }


}
