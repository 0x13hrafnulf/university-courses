package ob.BankMarketplace.general;

import ob.BankMarketplace.card.*;

public class Client {
    private int id;
    private String name;
    private boolean retired;
    private CardFactory cardFactory;
    private Card card;
    private Order order;
    public Client(int id, String name, boolean retired) {
        this.id = id;
        this.name = name;
        this.retired = retired;
    }
    public int getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public boolean isRetired() {
        return retired;
    }

    public String setCardType(CardType type) {
        cardFactory = type == CardType.VISA ? new VisaFactory() : new ElcardFactory();
        return "Card type was set.";
    }

    public Card getCard() {
        return this.card;
    }

    public String setOrder(Order order) {
        this.order = order;
        return "Order has been set.";
    }

    public String createCard(String number, int id) {
        card = cardFactory.createCard(number, id);
        System.out.printf("Card type selected -> %s\n", card.getType());
        return "Card has been created.";
    }

    public String pay () {
        System.out.printf("Payment method -> %s\n", card.createPayment(this.retired));
        System.out.printf("Processing -> %s\n", card.processPayment(this.order.getTotalCost()));
        return "Test";
    }
}
