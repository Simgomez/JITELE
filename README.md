# JITELE

Esta es una guía de los códigos anexados que se trabajan para realizar comunicaciones de radiofrecuencia, y que se usan para sistemas de telecomunicación como teleasistencia, domótica, monitoreo remoto de sensores o diferentes proyectos.

# LoRa

Es una tecnología de modulación de radio que se utiliza para diferentes ámbitos, como los mencionados anteriormente, destaca por ser económica y buen rango de cobertura, existen diferentes dispositivos en los que se integran chips de LoRa para poderse usar en diferentes proyectos, tales como la serie de microcontroladores basados en ESP 32 de la familia de dispositivos TTGO.

**Nota: Se recomienda conectar primero la antena correspondiente a los dispositivos TTGO ANTES que se alimenten de la fuente de energía, esto para evitar que se queme los módulos RF de los dispositivos.**

Los códigos referentes a “Envió - Recibe” son ejemplos de envió o recepción de datos utilizando la tecnología LoRa, compatibles con la familia de microcontroladores TTGO de diferentes modelos. Se debe descargar o importar la librería LoRa para hacer uso de varias funciones, también se deben ajustar las siguientes líneas de código:

#define SCK 5

#define MISO 19

#define MOSI 27

#define SS 18

#define RST 14

#define DIO0 26

Esto es porque en algunos modelos de la familia TTGO manejan pines diferentes para la comunicación LoRa, se debe consultar la distribución de pines del dispositivo que esté utilizando. Por otra parte, se debe seleccionar la banda de frecuencia utilizada según la región a la que se pertenece, esto por temas de reglamentación que se deben respetar, para ello se utilizan los siguientes comandos:

//433E6 (Para Región de Asia)

//866E6 (Para Región de Europa)

//915E6 (Para Región de Norte América)

Para regiones de Sur América se suele utilizar la banda 915E6.

### Gateway: 

También conocido como Puerta de enlace, son dispositivos mas robustos que permiten la interoperabilidad entre varios dispositivos que se conectan de manera simultánea, existen muchas empresas que fabrican y diseñan estos dispositivos, en esta ocasión, se hablara del modelo DLOS 8 de la empresa Dragino.
Este trabaja con tecnología LoRa al que los dispositivos se pueden conectar formando lo que se le conoce como, LORAWAN, este es un protocolo de comunicación que integra una red de dispositivos que se conectan a un módulo principal (En este caso el Gateway). 
Para poder realizar un envío de datos desde el Gateway hacia un servidor se requiere acceder a la terminal del Gateway por medio del software de preferencia como por ejemplo, Putty, acá se realizan comando del lenguaje Mosquitto para el envío de mensajes. El comando utilizado para enviar un dato a un servidor es: 

mosquitto_pub -h 18.119.33.222 -p 1883 -u admin -P public  -i dragino_Client -t 4567 -m "Hola"

La integración de todos estos dispositivos se consigue mediante un protocolo de red llamado MQTT, en este protocolo esencialmente se manejan parámetros como:


**Tópico:** Que se refiere a la credencial que manejamos para los dispositivos, es una especia de etiqueta que los dispositivos reconocen cuando se quieren conectar.

**Publicar:** Se refiere a grandes rasgos al proceso de enviar un paquete.

**Subscribir:** Se requiere a los dispositivos que, en lugar de enviar datos, se conectan a un servidor para leer los datos que se envían.

En el comando utilizado: mosquitto_pub -h 18.119.33.222 -p 1883 -u admin -P public  -i dragino_Client -t 4567 -m "Hola"

Se ingresa primero la ip a la que se quiere enviar el dato, seguido del puerto al cual nos queremos conectar (1883), seguido de las credenciales de seguridad como usuario o contraseña, para después ingresar el id de nuestro dispositivo (dragino_client), finalmente se coloca el tópico con el que se trabaja y el mensaje que se quiere enviar.


# GSM 


Sistema de comunicación de radio presente en sistemas móviles como los celulares, en el mercado existen diferentes módulos que manejan estas tecnologías, algunos de los cuales se pueden adquirir, son los módulos basados en Shields de tecnología GSM, estos nos permiten integrarse a algún sistema embebido como Arduino o Raspberry para, realizar funciones de mensajería SMS, llamadas o incluso algunos traen integrado un pequeño módulo de localización para ámbitos de navegación. Se requiere el uso de una SIM que se conecte al módulo GSM para poder funcionar.

Para la programación de estos módulos es requerido hacer uso de los comandos AT, en la que a través de diferentes secuencias realizan diferentes acciones como, por ejemplo: “AT+CMGF=1” para configurar un formato ASCII o “AT+CMGS=xxxx” para enviar un mensaje a algún número asignado. Dentro del repositorio se encuentra un ejemplo de envío de mensaje SMS asignado un número de teléfono y enviándolo en un intervalo de ciertos segundos.

El código utilizado para esta demostración se llama "GSM_Envio-Alarma", en este se encontrará con un ejemplo de cómo enviar mensajes SMS utilizando el módulo GSM conectado a un Arduino Uno, al inicio del código se declaran variables como los pines utilizados por el ShieldGSM, para este caso se utiliza un Shield M95 de Quectel:

int pwr = 2;                    // pin para power                
int eoff = 3;                   // pin para emergency off
int stat = 4;                   // pin para status
int led = 13;                   // pin para encender LED
int cont = 0;

Después de esto se encontrará con una sección del código que está comentada, la puede borrar si desea, esta sección comentada se usa para un ejemplo de sistema de alarma que será explicado brevemente más adelante pero no es necesaria para el funcionamiento del código.

Es importante que antes de iniciar el LOOP del código, se inicializan ciertos parámetros de configuración del módulo:

“AT” - (Inicializar el módulo)
“AT+CFUN=1" - (activa todas las funciones principales del módulo celular))
"AT+CMGF=1” - (configura el formato de MSM en ASCII))
"AT+CSQ"    - (evalúa la señal de la que dispone el dispositivo)

Es posible que se requiera el uso de más comandos AT adicionales para trabajar otras funciones, consulte un listado de comandos AT para utilizar los comandos que requiera según su proyecto.

Si desea enviar datos numéricos es requerido que antes se conviertan a formato ASCII, en nuestro caso se utiliza la siguiente función, pero puede utilizar cualquier función de preferencia:
dtostrf(valor_flotante, min_width, # digitos, variable_final);

La velocidad para, por ejemplo, que al enviar un SMS llegue de forma rápida al número asignado depende directamente de la capacidad del módulo/shield que se esté utilizando.

### Sistema de Alarma:

Podemos utilizar los módulos GSM para enviar mensajes según la lectura de algún sensor, por ejemplo en el código utilizamos la siguiente función:
En este caso se declaran las variables iniciales dependiendo del sensor que se esté utilizando (en mi caso es la sección que estaba comentada en el inicio),  en mi ejemplo se simula el valor de un flujo, en el que si llega a ser muy bajo nos envía directamente a la función “Emergencia:”.
 “Emergencia :” se activa cuando el valor de alguna variable (en este caso por ejemplo un flujo) esté por fuera de un umbral específico, de forma que si está por debajo o por encima de este rango podamos activar el envío de un SMS de emergencia con un texto de alerta, además de reducir el delay para que se envíe de forma continua hasta que la variable cambie o vuelva a su rango de normalidad. 
