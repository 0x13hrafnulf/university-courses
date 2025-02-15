package ob.Second.config;

import ob.Second.model.Client;
import org.springframework.amqp.core.*;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.support.converter.DefaultJackson2JavaTypeMapper;
import org.springframework.amqp.support.converter.Jackson2JsonMessageConverter;
import org.springframework.amqp.support.converter.MessageConverter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Map;

@Configuration
public class RabbitMQConfig {
    @Value("${rabbitmq.queue.clients.request.name}")
    private String clientsRequestQueue;

    @Value("${rabbitmq.queue.client.response.name}")
    private String clientResponseQueue;

    @Value("${rabbitmq.exchange.name}")
    private String exchange;

    @Value("${rabbitmq.routing.client.request.key}")
    private String clientRequestKey;

    @Value("${rabbitmq.routing.client.response.key}")
    private String clientResponseKey;

    @Bean
    public Queue getClientRequestQueue(){
        return new Queue(clientsRequestQueue);
    }

    // spring bean for queue (store json messages)
    @Bean
    public Queue getClientResponseQueue(){
        return new Queue(clientResponseQueue);
    }

    // spring bean for rabbitmq exchange
    @Bean
    public DirectExchange exchange(){
        return new DirectExchange(exchange);
    }

    // binding between queue and exchange using routing key
    @Bean
    public Binding clientRequestBinding(){
        return BindingBuilder
                .bind(getClientRequestQueue())
                .to(exchange())
                .with(clientRequestKey);
    }

    // binding between json queue and exchange using routing key
    @Bean
    public Binding clientResponseBinding(){
        return BindingBuilder
                .bind(getClientResponseQueue())
                .to(exchange())
                .with(clientResponseKey);
    }

    @Bean
    public MessageConverter converter(){
        DefaultJackson2JavaTypeMapper classMapper = new DefaultJackson2JavaTypeMapper();
        classMapper.setTrustedPackages("*");
        classMapper.setIdClassMapping(Map.of("client", Client.class));
        Jackson2JsonMessageConverter converter = new Jackson2JsonMessageConverter();
        converter.setClassMapper(classMapper);
        return converter;
    }

}
