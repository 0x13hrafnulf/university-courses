package ob.BankMarketplace.card;

public class VisaFactory implements CardFactory {
    @Override
    public Card createCard(String number, int id) {
        return new Visa(number, id);
    }
}
