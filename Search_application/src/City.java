import java.util.ArrayList;
import java.util.List;


/**
 * This is the city class，includes the city's name,latitude,longitude and the meals within thsi city
 */
public class City {
    private String name;
    private List<Meal> meals;
    private double latitude;
    private double longitude;


    public City(String name, double latitude, double longitude){
        this.name=name;
        this.latitude = latitude;
        this.longitude = longitude;
        meals=new ArrayList<>();
    }



    //getter and setter for attributes
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Meal> getMeals() {
        return meals;
    }

    public void setMeals(List<Meal> meals) {
        this.meals = meals;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }
}



