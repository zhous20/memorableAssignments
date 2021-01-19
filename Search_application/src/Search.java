import java.io.*;
import java.util.*;

/**
 * This class provides 3 static searching methods:bfs,dfs and shortestPath
 */
public class Search {

    /**
     * using breadth-first-search to find routes from startCity to endCity
     */
    static List<String> bfs(Map<String, List<String>> cities, String startCity, String endCity) {
        Set<String> visited = new HashSet<>(); // record whether a city has been visited
        Deque<String> queue = new LinkedList<>(); // use queue to implement bfs
        Map<String, String> path = new HashMap<>(); // record the path(end location->start location)
        String curCity = startCity;//current city
        visited.add(curCity);
        queue.add(curCity);
        boolean succeed = false;//early stop
        while ((!queue.isEmpty()) && (!succeed)) {
            curCity = queue.removeFirst();
            //search all the cities near current city
            if (cities.containsKey(curCity)) {
                for (String next : cities.get(curCity)) {
                    if (!visited.contains(next)) {
                        queue.addLast(next);
                        visited.add(next);
                        path.put(next, curCity);
                        if (next.equals(endCity)) {
                            succeed = true;
                            break;
                        }
                    }
                }
            }
        }

        //record the final route from start city to end city.
        List<String> result = new LinkedList<>();
        curCity = endCity;
        while (!curCity.equals(startCity)) {
            result.add(0, curCity);
            curCity = path.get(curCity);
        }
        result.add(0, curCity);
        return result;
    }


    //use recursive methods to finish dfs
    static void dfs(Map<String, List<String>> cities, String curCity, String endCity, Set<String> visited, Map<String, String> path) {
        if(cities.containsKey(curCity)) {
            for (String city : cities.get(curCity)) {
                if(!visited.contains(city)){
                    visited.add(city);
                    path.put(city,curCity);
                    if(city.equals(endCity)){
                        return ;
                    }else{
                        dfs(cities,city,endCity,visited,path);
                    }
                }
            }
        }
    }


    /**
     * using depth-first-search to find routes from startCity to endCity
     */
    static List<String> dfs(Map<String, List<String>> cities, String startCity, String endCity) {
        Set<String> visited = new HashSet<>();// record whether a city has been visited

        Map<String, String> path = new HashMap<>();// record the path(end location->start location)
        String curCity = startCity;//current city

        String lastCity = null;//record the last visited city
        dfs(cities,startCity,endCity,visited,path);

        List<String> result = new LinkedList<>();

        curCity = endCity;
        while (!curCity.equals(startCity)) {
            result.add(0, curCity);
            curCity = path.get(curCity);
        }
        result.add(0, curCity);
        return result;
    }


    /**
     * using shortestPath-search to find routes from startCity to endCity
     */
    static Path shortestPath(Map<String, List<String>> cities, String startCity, String endCity,
                             Map<String, City> cityMeal) {
        Queue<Path> priorityQueue = new PriorityQueue<>(100);//use priority queue to extract the shortest distance
        Path path = new Path(startCity, new Meal("", "", 0, ""));//start path 0
        priorityQueue.add(path);
        Set<String> yellow = new HashSet<>();//have visited but not for sure whether has found the shortest path
        Set<String> green = new HashSet<>();//have found the shortest path
        while (!priorityQueue.isEmpty()) {
            Path tmp = priorityQueue.remove();//extract the current shortest distance
            green.add(tmp.getCity());// this is the shortest path,add to the green set
            if (tmp.getCity().equals(endCity)) { // early stop if this is the end city
                return tmp;
            }
            //search each city near current city
            for (String next : cities.get(tmp.getCity())) {
                //if has visited and not in the green set
                if (yellow.contains(next) && (!green.contains(next))) {
                    //find the meal to eat ,need to exclude the same meal situation
                    Meal lastMeal = tmp.getMeal();
                    Meal meal = cityMeal.get(next.toUpperCase()).getMeals().get(0);
                    if (lastMeal.getRestaurant().equals(meal.getRestaurant()) &&
                            lastMeal.getChoice().equals(meal.getChoice())) {
                        meal = cityMeal.get(next.toUpperCase()).getMeals().get(1);
                    }

                    //we need to decrease the oldPath's value if its cost is higher than the new routes's cost
                    //but the java priority queue is implemented by binary heap,its api doesn't support decrease key
                    //so we use an alternative method to implement "decrease key" operation.
                    List<Path> paths = new ArrayList<>();
                    for (; ; ) {
                        Path oldPath = priorityQueue.remove();

                        if (oldPath.getCity().equals(next)) {
                            if (oldPath.getCost() > tmp.getCost() + meal.getPrice()) {
                                oldPath.setLast(tmp);
                                oldPath.setMeal(meal);
                                oldPath.setCost(tmp.getCost() + meal.getPrice());
                            }
                            paths.add(oldPath);
                            break;
                        }
                        paths.add(oldPath);
                    }

                    for (Path path1 : paths) {
                        priorityQueue.add(path1);
                    }


                }
                //if hasn't visited
                else {
                    //mark this city to have been visited
                    yellow.add(next);
                    //find the meal to eat ,need to exclude the same meal situation
                    Meal lastMeal = tmp.getMeal();
                    Meal meal = cityMeal.get(next.toUpperCase()).getMeals().get(0);
                    if (lastMeal.getRestaurant().equals(meal.getRestaurant()) &&
                            lastMeal.getChoice().equals(meal.getChoice())) {
                        meal = cityMeal.get(next.toUpperCase()).getMeals().get(1);
                    }
                    //now we have the meal ,create the path
                    Path nextPath = new Path(next, meal);
                    nextPath.setLast(tmp);
                    nextPath.setCost(tmp.getCost() + meal.getPrice());

                    priorityQueue.offer(nextPath);

                }

            }

        }
        return null;

    }

    /**
     * Test the 3 above methods
     */
    public static void main(String[] args) {
        Map<String, List<String>> cities = ReadGraph.getCityGraph(System.getProperty("user.dir") + "/src/connectedCities.txt");
        Map<String, List<Meal>> menu = ReadGraph.getMenu(System.getProperty("user.dir") + "/src/menu.csv");
        Map<String, City> cityMeal = ReadGraph.cityMeal(
                System.getProperty("user.dir") + "/src/USCities.csv",
                System.getProperty("user.dir") + "/src/mcdonalds.csv",
                System.getProperty("user.dir") + "/src/burgerking.csv",
                System.getProperty("user.dir") + "/src/wendys.csv",
                menu
        );
        List<String> dfsResult = dfs(cities, "Boston", "Minneapolis");
        List<String> bfsResult = bfs(cities, "Boston", "Minneapolis");
        Path shortestResult = shortestPath(cities, "Boston", "Minneapolis", cityMeal);

        StringBuilder bfsPath = new StringBuilder("BFS:");
        for (String tmp : bfsResult) {
            bfsPath.append(tmp);
            bfsPath.append(",");
        }
        System.out.println(bfsPath.substring(0, bfsPath.length() - 1).toString());

        StringBuilder dfsPath = new StringBuilder("DFS:");
        for (String tmp : dfsResult) {
            dfsPath.append(tmp);
            dfsPath.append(",");
        }
        System.out.println(dfsPath.substring(0, dfsPath.length() - 1).toString());


        StringBuilder shortestPath = new StringBuilder(String.format("%-20s", "City") +
                String.format("%-30s", "Meal Choice") +
                String.format("%-20s", "Cost of Meal($)") + "\n");
        List<Path> orderShortestPath = new LinkedList<>();

        while (shortestResult != null) {
            orderShortestPath.add(0, shortestResult);
            shortestResult = shortestResult.getLast();
        }

        for (Path tmp : orderShortestPath) {
            shortestPath.append(String.format("%-20s", tmp.getCity()) +
                    String.format("%-30s", tmp.getMeal().getChoice()) +
                    String.format("%-20s", tmp.getMeal().getPrice()) + "\n");
        }
        System.out.println(shortestPath.toString());

        try {
            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(System.getProperty("user.dir") + "/src/a2_out.txt")));
            bufferedWriter.write(bfsPath.substring(0, bfsPath.length() - 1).toString());
            bufferedWriter.write("\n");
            bufferedWriter.write(dfsPath.substring(0, dfsPath.length() - 1).toString());
            bufferedWriter.write("\n");
            bufferedWriter.write(shortestPath.toString());
            bufferedWriter.flush();
            bufferedWriter.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
