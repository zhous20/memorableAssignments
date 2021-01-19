/**
 * This is the meal class,includes the meal's restaurant and choice,price and comment
 * Besides the class implement comparable according to the price
 */
public class Meal implements Comparable {
    private String restaurant;
    private String choice;
    private double price;
    private String comment;


    public Meal(String restaurant, String choice, double price, String comment) {
        this.restaurant=restaurant;
        this.choice=choice;
        this.price=price;
        this.comment=comment;
    }

    //getter and setter for attributes
    public String getRestaurant() {
        return restaurant;
    }

    public void setRestaurant(String restaurant) {
        this.restaurant = restaurant;
    }

    public String getChoice() {
        return choice;
    }

    public void setChoice(String choice) {
        this.choice = choice;
    }


    public String getComment() {
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }


    @Override
    public boolean equals(Object obj) {
        return price==((Meal)obj).getPrice();
    }


    @Override
    public int compareTo(Object o) {
        if(price<((Meal)o).getPrice()){
            return -1;
        }else if(price>((Meal)o).getPrice()){
            return  1;
        }else {
            return 0;
        }
    }
}