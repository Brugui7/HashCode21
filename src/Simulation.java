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
    public ArrayList<IntersectionScheduled> scheduleds;



    /**
     * LA MAGIA
     * Reparte las pizzas entre los equipos intentando maximizar el número de ingredientes distintos
     */
    void magic() {
        scheduleds = new ArrayList<>();
        for (Intersection intersection : intersections.values()){
            IntersectionScheduled intScheduled = new IntersectionScheduled(intersection.id);
            for (Street street : intersection.in){
                intScheduled.schedule.put(street.name, 1);
            }
            scheduleds.add(intScheduled);
        }
    }





    public Simulation() {
        this.streets = new HashMap<>();
        this.paths = new ArrayList<>();
        this.intersections = new HashMap<>();
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
