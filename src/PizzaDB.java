import java.util.ArrayList;

class PizzaDB {
    int teamsOf2, teamsOf3, teamsOf4;
    public ArrayList<Pizza> pizzas;
    public ArrayList<ArrayList<Integer>> delivering;
    public int totalIng;

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
        System.out.println("maximas repeticiones: ");
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
