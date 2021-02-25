import com.sun.deploy.util.ArrayUtil;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Reader {
    public static Simulation read(String path){
        Simulation simulation = new Simulation();


        List<String> lines = new ArrayList<>();

        try {
            lines = Files.readAllLines(Paths.get(path));
        } catch (IOException e) {
            e.printStackTrace();
        }

        String[] firstInfo = lines.get(0).split(" ");

        //lee primera línea
        simulation.duration = Integer.valueOf(firstInfo[0]);
        simulation.intersectionsNumber = Integer.valueOf(firstInfo[1]);
        simulation.streetsNumber = Integer.valueOf(firstInfo[2]);
        simulation.carsNumber = Integer.valueOf(firstInfo[3]);
        simulation.bonusPoints = Integer.valueOf(firstInfo[4]);

        System.out.println("\t" + "Duración: " + simulation.duration + "\n" +
                "\tIntersecciones: " + simulation.intersectionsNumber + "\n" +
                "\t" + "Calles: " + simulation.streetsNumber + "\n\tBonus Points: " + simulation.bonusPoints
        );

        HashMap<Integer, Intersection> intersections = new HashMap<>();
        int lineCounter = 1;
        for (int i = 0; i < simulation.streetsNumber; ++i){
            String[] streetData = lines.get(lineCounter++).split(" ");
            Street street = new Street();
            street.name = streetData[2];
            street.time = Integer.valueOf(streetData[3]);
            int start = Integer.valueOf(streetData[0]);
            int end = Integer.valueOf(streetData[1]);


            if (!intersections.containsKey(start)){
                intersections.put(start, new Intersection(start));
            }
            intersections.get(start).out.add(street);

            if (!intersections.containsKey(end)){
                intersections.put(end, new Intersection(end));
            }
            intersections.get(end).in.add(street);

        }

        HashMap<String, Integer> carsByStreet = new HashMap<>();


        for (int i = 0; i < simulation.carsNumber; ++i){
            String[] carPath = lines.get(lineCounter++).split(" ");
            int streets = carPath.length;
            for (int j = 1; j < streets; j++) {
                if (!carsByStreet.containsKey(carPath[j])){
                    System.out.println("no contiene");
                    carsByStreet.put(carPath[j], 0);
                }
                carsByStreet.put(carPath[j], carsByStreet.get(carPath[j]) + 1);
                //System.out.println("Por la calle " + carPath[j] + " pasan " + carsByStreet.get(carPath[j]));
            }
        }
        simulation.carsByStreet = carsByStreet;
        /*Collections.sort(data, new Comparator<Pizza>() {
            @Override
            public int compare(Pizza p1, Pizza p2) {
                if (p1.ingN == p2.ingN) return 0;
                return p1.ingN > p2.ingN ? -1 : 1;
            }
        });

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
        System.out.println(stringAux.replace(",", ""));*/


        simulation.intersections = intersections;
        //db.totalIng = ingByPizza.size();
        return simulation;
    }
}

