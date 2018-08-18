# DHCP

## Protocolo de Configuración Dinámica de Host

* Hay 1 servidor por red (NO se puede más de uno)

### Leasing

Entrega de un recurso. Préstamo. En este caso una IP. Tiene un tiempo de 
préstamo

Hay un default-lease-time: tiempo opcional de renegociación.
max-lease-time: Luego de ese tiempo ya sé que la perdí.


**OJO CON EL TRANSACTION ID**: porque este indica qué paquetes pertenecen a 
una misma negociación

#### Orden

1. Discover: El host se propone pedir una IP, larga el mensaje a 255.255.255.255

1. Offer: El servidor le ofrece una IP, en el dest del paquete hay data

1. Request: Pedido de la IP al servidor

1. ACK

El puerto que utiliza el cliente no es efímero, es un puerto fijo. Siempre 68. 

Y el "servidor" siempre recibe por el puerto 67

```
Se especifica la rubred la máscara y el router por el cual se sale
```

bbbb 789abc ip 10.1.28.9 10.1.74.9
