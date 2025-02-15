package ob.Second.service;

import ob.Second.model.Client;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.annotation.RabbitHandler;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import java.util.List;


@Component
@RabbitListener(queues = {"${rabbitmq.queue.clients.request.name}"})
public class RabbitMQHandler {

    @Value("${rabbitmq.exchange.name}")
    private String exchange;

    @Value("${rabbitmq.routing.client.request.key}")
    private String clientRequestKey;

    @Value("${rabbitmq.routing.client.response.key}")
    private String clientResponseKey;
    private static final Logger LOGGER = LoggerFactory.getLogger(RabbitMQHandler.class);
    private ClientService clientService;

    @Autowired
    public RabbitMQHandler(RabbitTemplate rabbitTemplate, ClientService clientService) {
        this.clientService = clientService;
    }

    @RabbitHandler
    public List<Client> getClients(String message) {
        return clientService.getClients();
    }
    @RabbitHandler
    public String addClient(Client client){
        clientService.addClient(client);
        return "Client has been added: " + client.getFIO();
    }

}
