package ob.First.service;

import ob.First.model.Client;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.AsyncRabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.concurrent.ExecutionException;


@Component
public class RabbitMQHandler {
    @Value("${rabbitmq.exchange.name}")
    private String exchange;

    @Value("${rabbitmq.routing.client.request.key}")
    private String clientRequestKey;

    @Value("${rabbitmq.routing.client.response.key}")
    private String clientResponseKey;

    private static final Logger LOGGER = LoggerFactory.getLogger(RabbitMQHandler.class);
    private AsyncRabbitTemplate asyncRabbitTemplate;

    @Autowired
    public RabbitMQHandler(AsyncRabbitTemplate asyncRabbitTemplate) {
        this.asyncRabbitTemplate = asyncRabbitTemplate;
    }

    public List<Client> requestGetClients() throws ExecutionException, InterruptedException {
        LOGGER.info(String.format("Get clients request sent."));
        AsyncRabbitTemplate.RabbitConverterFuture<List<Client>> future =
                asyncRabbitTemplate.convertSendAndReceiveAsType(exchange, clientRequestKey, "", new ParameterizedTypeReference<>() {});
        return future.get();
    }
    public String requestAddClient(Client client) throws ExecutionException, InterruptedException {
        LOGGER.info(String.format("Add Client request sent -> %s", client.toString()));
        AsyncRabbitTemplate.RabbitConverterFuture<String> future = asyncRabbitTemplate.convertSendAndReceive(exchange, clientRequestKey, client);
        return future.get();
    }

}
