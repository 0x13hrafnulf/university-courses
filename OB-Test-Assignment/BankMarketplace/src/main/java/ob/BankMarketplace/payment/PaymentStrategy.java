package ob.BankMarketplace.payment;

public interface PaymentStrategy {
    public String processPayment(double amount);
    public String getType();
}
