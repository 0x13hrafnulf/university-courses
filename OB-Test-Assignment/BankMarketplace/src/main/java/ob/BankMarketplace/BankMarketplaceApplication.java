package ob.BankMarketplace;

import ob.BankMarketplace.card.CardType;
import ob.BankMarketplace.general.Client;
import ob.BankMarketplace.general.Inventory;
import ob.BankMarketplace.general.Item;
import ob.BankMarketplace.general.Order;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.util.HashMap;
import java.util.Locale;
import java.util.Random;
import java.util.Scanner;

@SpringBootApplication
public class BankMarketplaceApplication implements CommandLineRunner {

	private static Scanner scanner = new Scanner(System.in);
	private HashMap<Integer, Client> clients = new HashMap<Integer, Client>();
	private Inventory inventory;

	public static void main(String[] args) {
		SpringApplication.run(BankMarketplaceApplication.class, args);
	}

	public void generateInventory() throws Exception
	{
		Random rand = new Random();
		inventory = new Inventory();

		for(int i = 5; i < 10; ++i)
		{
			double price = 500.0 + (i % 5) * 100;
			Item item = new Item(i % 5, String.format("Iphone%d", i), price, "Phone");
			inventory.addProducts(item, rand.nextInt(10));
		}
		for(int i = 5; i < 10; ++i)
		{
			double price = 500.0 + (i % 5) * 50;
			Item item = new Item(i, String.format("Samsung%d", i), price, "Phone");
			inventory.addProducts(item, rand.nextInt(10));
		}
	}
	public void generateClients()
	{
		Random rand = new Random();
		String[] names = {"James", "Robert", "John", "Michael", "David", "William", "Richard", "Joseph", "Thomas", "Charles"};
		String[] surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
		for(int i = 0; i < 10; ++i)
		{
			boolean retired = rand.nextBoolean();
			Client client = new Client(i, String.format("%s %s", names[rand.nextInt(10)], surnames[rand.nextInt(10)]), retired);

			String number = String.format("%d", rand.nextInt(50));
			clients.put(i, client);
		}
	}

	@Override
	public void run(String[] args) throws Exception
	{
		generateClients();
		generateInventory();

		System.out.println("Enter user ID:");
		int userID = scanner.nextInt();
		scanner.nextLine();
		if (!clients.containsKey(userID))
		{
			System.out.println("Enter your full name:");
			String userName = scanner.nextLine();
			System.out.println("Are you retired (Y/N)?)");
			String answer = scanner.nextLine().toUpperCase().trim();
			boolean retired = answer.equals("Y");
			clients.put(userID, new Client(userID, userName, retired));
		}
		Client currentClient = clients.get(userID);
		System.out.format("Welcome, %s. Retired Status: %b\n", currentClient.getName(), currentClient.isRetired());
		System.out.println("Check our mobile shop. Smartphones' list:" );
		boolean shop = true;
		Order order = new Order();
		while (shop)
		{
			inventory.getInventory().forEach((k, v) -> {
				System.out.format("(ID:%d) => key: %s, amount: %d, price: %.2f\n", k, inventory.getItem(k).getName(), v, inventory.getItem(k).getPrice());
			});
			System.out.println("Choose items for purchase: <ID>");
			int id = scanner.nextInt();
			scanner.nextLine();

			order.addItem(inventory.getItems().get(id));

			System.out.println("Do you wish to continue shopping (Y/N)?)");
			String answer = scanner.nextLine().trim().toUpperCase(Locale.ROOT);
			shop = answer.equals("Y") ? true : false;
		}

		System.out.println("Order:\n");
		order.getItems().forEach(k -> {
			System.out.format("(ID:%d) => key: %s\n", k.getId(), k.getName());
		});
		System.out.format("Sum:%.2f\n", order.getTotalCost());

		currentClient.setOrder(order);
		if (currentClient.getCard() == null)
		{
			System.out.println("Please select your payment method: 1) Visa; 2) Elcard. Enter a number (1,2).");
			String answer = scanner.nextLine().trim().toUpperCase();
			CardType cardType = answer.equals("1") ? CardType.VISA : CardType.ELCARD;
			currentClient.setCardType(cardType);
			System.out.println("Enter your card number:");
			String number = scanner.nextLine();

			Random rand = new Random();
			int id = rand.nextInt();
			currentClient.createCard(number.trim(), id);

			currentClient.pay();
		}
		System.exit(0);
	}

}
