package ob.BankMarketplace.card;
import ob.BankMarketplace.payment.PaymentStrategy;

public abstract class Card {
    protected String number;
    protected int id;
    protected String type;

    public String getType() {
        return type;
    }

    protected PaymentStrategy paymentStrategy;
    public abstract String createPayment(boolean retired);
    public abstract String processPayment(double amount);

}
