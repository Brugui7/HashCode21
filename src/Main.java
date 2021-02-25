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

    public static void main(String[] args) {
        //getDatasetsInfo();
        Simulation pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\a.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "a");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\b.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "b");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\c.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "c");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\d.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "d");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\e.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "e");

        pizzaDB = Reader.read("C:\\Users\\Brugui\\IdeaWorkspace\\hashcode21practice\\src\\datasets\\f.txt");
        pizzaDB.magic();
        Writer.write(pizzaDB.scheduleds, "f");

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


