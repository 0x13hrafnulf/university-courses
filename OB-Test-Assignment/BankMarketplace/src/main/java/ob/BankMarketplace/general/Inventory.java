package ob.BankMarketplace.general;

import java.util.ArrayList;
import java.util.HashMap;

public class Inventory
{
    private ArrayList<Item> items;
    private HashMap<Integer, Integer> inventory;

    public Inventory() {
        this.items = new ArrayList<Item>();
        this.inventory = new HashMap<Integer, Integer>();
    }

    public void addProducts(final Item item, final int amount) throws Exception {
        if (item != null) {
            items.add(item);
            final int currentAmount = this.inventory.getOrDefault(item.getId(), 0);
            this.inventory.put(item.getId(), currentAmount + amount);
        } else {
            throw new Exception("You cannot add Null objects to items!");
        }
    }

    public void removeProducts(final Item item, final int amount) throws Exception {
        if (this.inventory.get(item) > amount) {
            this.inventory.replace(item.getId(), this.inventory.get(item.getId()) - amount);
        } else if (this.inventory.get(item.getId()) == amount) {
            this.inventory.replace(item.getId(), 0);
        } else {
            throw new Exception(String.format("Cannot remove %d instances" +
                    " of product as there are only %d instances!", amount, this.inventory.get(item.getId())));
        }
    }
    public ArrayList<Item> getItems()
    {
        return items;
    }
    public HashMap<Integer, Integer> getInventory()
    {
        return inventory;
    }
    public Item getItem(Integer id)
    {
        return items.get(id);
    }
}

