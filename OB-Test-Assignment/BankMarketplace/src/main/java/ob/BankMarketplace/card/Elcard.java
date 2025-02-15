package ob.BankMarketplace.card;

import ob.BankMarketplace.payment.IPC;
import ob.BankMarketplace.payment.Way4;

public class Elcard extends Card {

    public Elcard(String number, int id) {
        this.number = number;
        this.id = id;
        this.type = "Elcard";
    }
    @Override
    public String createPayment(boolean retired) {
        this.paymentStrategy = retired ? new IPC() : new Way4();
        return this.paymentStrategy.getType();
    }

    @Override
    public String processPayment(double amount) {
        return this.paymentStrategy.processPayment(amount);
    }


}
