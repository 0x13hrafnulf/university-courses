package ob.Second.service;

import ob.Second.model.Client;
import ob.Second.repo.ClientRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
public class ClientService {

    private ClientRepository clientRepository;
    @Autowired
    public ClientService(ClientRepository clientRepository) {
        this.clientRepository = clientRepository;
    }
    public List<Client> getClients() {
        return clientRepository.findAll();
    }

    @Transactional
    public Client addClient(Client client) {
        return clientRepository.save(client);
    }
}
