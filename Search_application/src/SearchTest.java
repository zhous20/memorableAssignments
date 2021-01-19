import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import static org.junit.Assert.*;


public class SearchTest {

    @org.junit.Test
    public void testBfs() throws Exception {
        Map<String, List<String>> cities = ReadGraph.getCityGraph(System.getProperty("user.dir") + "/src/connectedCities.txt");
        List<String> bfsResult = Search.bfs(cities, "Boston", "Minneapolis");
        String BFS_BOSTON_MINNEAPOLIS = "BFS:Boston,New York City,Pittsburgh,Columbus,Chicago,Minneapolis";

        StringBuilder bfsPath = new StringBuilder("BFS:");
        for (String tmp : bfsResult) {
            bfsPath.append(tmp);
            bfsPath.append(",");
        }
        assertEquals(BFS_BOSTON_MINNEAPOLIS, bfsPath.substring(0, bfsPath.length() - 1).toString());
    }

    @org.junit.Test
    public void testDfs() throws Exception {
        Map<String, List<String>> cities = ReadGraph.getCityGraph(System.getProperty("user.dir") + "/src/connectedCities.txt");
        List<String> dfsResult = Search.dfs(cities, "Boston", "Minneapolis");

        String DFS_BOSTON_MINNEAPOLIS = "DFS:Boston,New York City,Philadelphia,Baltimore,Washington,Charlotte,Atlanta,Nashville,Columbus,Indianapolis,St. Louis,Kansas City,Denver,Salt Lake City,Las Vegas,Los Angeles,San Francisco,Portland,Seattle,Minneapolis";

        StringBuilder dfsPath = new StringBuilder("DFS:");
        for (String tmp : dfsResult) {
            dfsPath.append(tmp);
            dfsPath.append(",");
        }
        assertEquals(DFS_BOSTON_MINNEAPOLIS, dfsPath.substring(0, dfsPath.length() - 1).toString());
    }

    @org.junit.Test
    public void testShortestPath() throws Exception {
        Map<String, List<String>> cities = ReadGraph.getCityGraph(System.getProperty("user.dir") + "/src/connectedCities.txt");
        Map<String, List<Meal>> menu = ReadGraph.getMenu(System.getProperty("user.dir") + "/src/menu.csv");
        Map<String, City> cityMeal = ReadGraph.cityMeal(
                System.getProperty("user.dir") + "/src/USCities.csv",
                System.getProperty("user.dir") + "/src/mcdonalds.csv",
                System.getProperty("user.dir") + "/src/burgerking.csv",
                System.getProperty("user.dir") + "/src/wendys.csv",
                menu
        );

        String SHORTEST_BOSTON_MINNEAPOLIS = "Boston,,0.0\n" +
                "New York City,McChicken - Meal,3.79\n" +
                "Pittsburgh,Double Cheeseburger - Meal,4.38\n" +
                "Columbus,McChicken - Meal,3.79\n" +
                "Chicago,Double Cheeseburger - Meal,4.38\n" +
                "Minneapolis,McChicken - Meal,3.79\n";
        Path shortestResult = Search.shortestPath(cities, "Boston", "Minneapolis", cityMeal);
        StringBuilder shortestPath = new StringBuilder();
        List<Path> orderShortestPath = new LinkedList<>();

        while (shortestResult != null) {
            orderShortestPath.add(0, shortestResult);
            shortestResult = shortestResult.getLast();
        }

        for (Path tmp : orderShortestPath) {
            shortestPath.append(String.format("%s,", tmp.getCity()) +
                    String.format("%s,", tmp.getMeal().getChoice()) +
                    String.format("%s", tmp.getMeal().getPrice()) + "\n");
        }
        assertEquals(SHORTEST_BOSTON_MINNEAPOLIS, shortestPath.toString());
    }
}