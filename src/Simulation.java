import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Simulation {
    public int intersectionsNumber;
    public int duration;
    public int streetsNumber;
    public int carsNumber;
    public int bonusPoints;
    private HashMap<String, Street> streets;
    private List<CarPath> paths;
    public HashMap<Integer, Intersection> intersections;
    public HashMap<String, Integer> carsByStreet;
    public ArrayList<IntersectionScheduled> scheduleds;



    /**
     * LA MAGIA
     * Reparte las pizzas entre los equipos intentando maximizar el número de ingredientes distintos
     */
    void magic() {
        scheduleds = new ArrayList<>();
        for (Intersection intersection : intersections.values()){
            IntersectionScheduled intScheduled = new IntersectionScheduled(intersection.id);
            int time = intersection.in.size() < 3 ? 10 : 1;

            for (Street street : intersection.in){
                if (carsByStreet.get(street.name) == null) continue;
                int cars = carsByStreet.get(street.name);
                //carsByStreet.put(street.name, carsByStreet.get(street.name) - 1);

                intScheduled.schedule.put(street.name,  1);
                duration--;
            }
            if (intScheduled.schedule.size() == 0) continue;
            scheduleds.add(intScheduled);
            //scheduleds.get(scheduleds.size() - 1);
        }
        System.out.println("Duracion restante: " + duration);
    }





    public Simulation() {
        this.streets = new HashMap<>();
        this.paths = new ArrayList<>();
        this.intersections = new HashMap<>();
        this.carsByStreet = new HashMap<>();
    }

    public Simulation(int intersectionsNumber, int duration, int streetsNumber, int carsNumber, int bonusPoints) {
        this.intersectionsNumber = intersectionsNumber;
        this.duration = duration;
        this.streetsNumber = streetsNumber;
        this.carsNumber = carsNumber;
        this.bonusPoints = bonusPoints;
    }

    public Simulation(int intersectionsNumber, int duration, int streetsNumber, int carsNumber, int bonusPoints, HashMap<String, Street> streets) {
        this.intersectionsNumber = intersectionsNumber;
        this.duration = duration;
        this.streetsNumber = streetsNumber;
        this.carsNumber = carsNumber;
        this.bonusPoints = bonusPoints;
        this.streets = streets;
    }
}
