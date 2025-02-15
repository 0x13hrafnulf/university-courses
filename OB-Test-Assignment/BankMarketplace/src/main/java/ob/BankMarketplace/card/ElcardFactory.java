package ob.BankMarketplace.card;

public class ElcardFactory implements CardFactory {

    @Override
    public Card createCard(String number, int id) {
        return new Elcard(number, id);
    }
}
