import java.io.*;
import java.util.*;

/**
 * This class provides three static methods to read cities,menus,and the restaurants.
 */
public class ReadGraph {
    /**
     * Read the connection between cities
     */
    public static Map<String,List<String>> getCityGraph(String filename){
        Map<String,List<String>> result=new HashMap<>();
        try {
            BufferedReader bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
            String line;
            while ((line=bufferedReader.readLine())!=null){
                String[] cities=line.split(",");
                if(!result.containsKey(cities[0].trim())){
                    result.put(cities[0].trim(),new ArrayList<>());
                }
                result.get(cities[0].trim()).add(cities[1].trim());


            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }


    /**
     * Read the menus provided by 3 restaurants
     */
    public static Map<String,List<Meal>> getMenu(String filename){
        Map<String,List<Meal>> result=new HashMap<>();
        try {
            BufferedReader bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
            String line;
            bufferedReader.readLine();
            while ((line=bufferedReader.readLine())!=null){
                String[] meals=line.split(",");
                if(!result.containsKey(meals[0])){
                    result.put(meals[0],new ArrayList<>());
                }
                Meal meal=new Meal(meals[0],meals[1],Double.valueOf(meals[2].substring(1)),meals[3]);
                result.get(meals[0]).add(meal);


            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;

    }


    /**
     * Read the cities location and the restaurants location.
     * And for each cities find the restaurants near( within 0.5 degree) it.
     */
    public static Map<String,City> cityMeal(String city_loc,
                                                  String mc_loc,
                                                  String burger_loc,
                                                  String wendys_loc,
                                                  Map<String,List<Meal>> menu){
        Map<String,City> result=new HashMap<>();
        List<Restaurant> restaurants=new ArrayList<>();

        try {
            BufferedReader bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(city_loc)));
            String line;
            bufferedReader.readLine();
            while ((line=bufferedReader.readLine())!=null){
                String[] cities=line.split(",");
                City city=new City(cities[3],Double.valueOf(cities[4]),Double.valueOf(cities[5]));
                if(!result.containsKey(cities[0])){
                    result.put(cities[3],city);
                }
            }


            bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(mc_loc)));
            while ((line=bufferedReader.readLine())!=null){
                String[] restaurant=line.split(",");
                Restaurant restaurant1=new Restaurant("McDonald’s",Double.valueOf(restaurant[1]),Double.valueOf(restaurant[0]));
                restaurants.add(restaurant1);
            }

            bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(burger_loc)));
            while ((line=bufferedReader.readLine())!=null){
                String[] restaurant=line.split(",");
                Restaurant restaurant1=new Restaurant("Burger King",Double.valueOf(restaurant[1]),Double.valueOf(restaurant[0]));
                restaurants.add(restaurant1);
            }

            bufferedReader=new BufferedReader(new InputStreamReader(new FileInputStream(wendys_loc)));
            while ((line=bufferedReader.readLine())!=null){
                String[] restaurant=line.split(",");
                Restaurant restaurant1=new Restaurant("Wendy’s",Double.valueOf(restaurant[1]),Double.valueOf(restaurant[0]));
                restaurants.add(restaurant1);
            }

            for(Map.Entry<String, City> entry:result.entrySet()){
                City tmp=entry.getValue();
                Set<String> available_restaurants=new HashSet<>();
                for(Restaurant restaurant:restaurants){
                    if(Math.abs(tmp.getLatitude()-restaurant.getLatitude())<=0.5 &&
                            Math.abs(tmp.getLongitude()-restaurant.getLongitude())<=0.5){
                        available_restaurants.add(restaurant.getName());

                    }
                }

                Iterator<String> iterator=available_restaurants.iterator();
                while (iterator.hasNext()){
                    tmp.getMeals().addAll(menu.get(iterator.next()));
                }
                Collections.sort(tmp.getMeals());
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;


    }
}
