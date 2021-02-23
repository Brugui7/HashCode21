import com.sun.deploy.util.ArrayUtil;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Reader {
    public static PizzaDB read(String path){
        ArrayList<Pizza>  data = new ArrayList<>();
        List<String> lines = new ArrayList<>();

        TreeMap<Integer, Integer> pizzaByIngN = new TreeMap<>();
        HashMap<String, Integer> ingByPizza = new HashMap<>();

        try {
            lines = Files.readAllLines(Paths.get(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
        int pizzasNumber, teamsOf2, teamsOf3, teamsOf4, maxIng = 0;
        String[] firstInfo = lines.get(0).split(" ");

        //lee primera línea
        pizzasNumber = Integer.valueOf(firstInfo[0]);
        teamsOf2 = Integer.valueOf(firstInfo[1]);
        teamsOf3 = Integer.valueOf(firstInfo[2]);
        teamsOf4 = Integer.valueOf(firstInfo[3]);

        System.out.println("\t" + "Pizzas: " + pizzasNumber + "\n\tEquipos de 2: " + teamsOf2 + "\n\t" + "Equipos de 3: " + teamsOf3 + "\n\tEquipos de 4: " + teamsOf4);

        int lineCounter = 1;
        for (int i = 0; i < pizzasNumber; ++i){

            Pizza pizza = new Pizza();
            pizza.index = i;

            String[] ingredients = lines.get(lineCounter++).split(" ");
            int ingNumber = Integer.valueOf(ingredients[0]);
            if (!pizzaByIngN.containsKey(ingNumber)){
                pizzaByIngN.put(ingNumber, 0);
            }

            pizzaByIngN.put(ingNumber, pizzaByIngN.get(ingNumber) + 1);

            for (int j = 1; j < ingNumber + 1; j++){
                String ing = ingredients[j];
                pizza.ingredientsArray.add(ing);

                if (!ingByPizza.containsKey(ing)){
                    ingByPizza.put(ing, 0);
                    maxIng++;
                }
                ingByPizza.put(ing, ingByPizza.get(ing) + 1);
            }
            data.add(pizza);
        }

        System.out.println("\n\tPizzas por nº de ingredientes RAW");
        System.out.println("\t" + pizzaByIngN.entrySet());

        for (int i = 0; i < maxIng; i++) {
            if (!pizzaByIngN.containsKey(i)) pizzaByIngN.put(i, 0);
        }

        System.out.println("\n\tPizzas por nº de ingredientes for histogram");
        List<Integer> aux = new ArrayList(pizzaByIngN.values());
        String stringAux = "\t" + aux;
        System.out.println(stringAux.replace(",", ""));

        System.out.println("\n\t" + "Ingredientes por pizza en la que están RAW");
        System.out.println("\t" + ingByPizza.entrySet());
        System.out.println("\n\t" + "Ingredientes por pizza en la que están for histogram");
         aux = new ArrayList(ingByPizza.values());
        Collections.sort(aux);
        stringAux = "\t" + aux;
        System.out.println(stringAux.replace(",", ""));


        return new PizzaDB(teamsOf2, teamsOf3, teamsOf4, data);
    }
}

