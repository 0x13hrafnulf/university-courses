package ob.BankMarketplace.payment;

public class Way4 implements PaymentStrategy {

    private String type = "Way4";
    @Override
    public String getType() {
        return type;
    }

    @Override
    public String processPayment(double amount) {
        return String.format("Way4 payment: %.2f", amount);
    }
}
