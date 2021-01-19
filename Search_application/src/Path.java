/**
 * This is the shortest path *node* class
 * Path class records the cur city and from which it comes from
 * Also this path record the meal passenger has at this city
 * The cost attribute record the total money one consumes from the start city.
 */
public class Path implements Comparable{
    private String city;

    private Path last;

    private Meal meal;

    private double cost;

    public Path(String city, Meal meal) {
        this.city = city;
        this.meal = meal;
        last = null;
    }

    //getter and setter for the attributes
    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public Meal getMeal() {
        return meal;
    }

    public void setMeal(Meal meal) {
        this.meal = meal;
    }

    @Override
    public int compareTo(Object o) {
        if(cost<((Path)o).getCost()){
            return -1;
        }else if (cost>((Path)o).getCost()){
            return 1;
        }else{
            return 0;
        }
    }



    public Path getLast() {
        return last;
    }

    public void setLast(Path last) {
        this.last = last;
    }

    public double getCost() {
        return cost;
    }

    public void setCost(double cost) {
        this.cost = cost;
    }
}
