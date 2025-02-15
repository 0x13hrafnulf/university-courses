package ob.BankMarketplace.general;

import java.util.ArrayList;

public class Order
{
    private double totalCost = 0;
    private ArrayList<Item> items;

    public Order()
    {
        this.items = new ArrayList<Item>();
    }

    public void setTotalCost(double cost)
    {
        this.totalCost += cost;
    }

    public double getTotalCost()
    {
        return totalCost;
    }

    public void addItem(Item item)
    {
        items.add(item);
        setTotalCost(item.getPrice());
    }
    public ArrayList<Item> getItems() {
        return items;
    }

}


