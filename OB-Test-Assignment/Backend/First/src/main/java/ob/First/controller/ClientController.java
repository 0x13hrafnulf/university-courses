package ob.First.controller;

import ob.First.model.Client;
import ob.First.service.RabbitMQHandler;
import org.apache.coyote.Response;
import org.apache.logging.log4j.message.Message;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.concurrent.ExecutionException;

@RestController
public class ClientController {

    private RabbitMQHandler rabbitMQHandler;

    @Autowired
    public ClientController(RabbitMQHandler rabbitMQHandler) {
        this.rabbitMQHandler = rabbitMQHandler;
    }

    @GetMapping(path ="/getClients")
    public List<Client> getClients() throws ExecutionException, InterruptedException {
        return rabbitMQHandler.requestGetClients();
    }

    @PostMapping(value = "/addClient", consumes = "application/json", produces ="application/json")
    public String addClient(@RequestBody Client client) throws ExecutionException, InterruptedException {
        System.out.println("Test");
        return rabbitMQHandler.requestAddClient(client);
    }
}

