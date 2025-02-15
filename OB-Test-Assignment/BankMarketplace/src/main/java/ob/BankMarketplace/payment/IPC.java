package ob.BankMarketplace.payment;

public class IPC implements PaymentStrategy {

    private String type = "IPC";

    @Override
    public String getType() {
        return type;
    }
    @Override
    public String processPayment(double amount) {
        return String.format("IPC payment: %.2f", amount);
    }
}
