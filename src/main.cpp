#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
// int led_gpio = 15;
int columnas[] = {13, 12, 14, 27, 32, 33, 25, 26, 15, 23, 22, 5, 18, 19, 21, 3};
int filas[] = {17, 16, 2, 4};
int tiempo = 150;
char auxPatron = '0';

const char *ssid = "EGMC DEPTO";
const char *password = "Cuartos27";

const char *mqtt_server = "driver.cloudmqtt.com";
const int mqtt_port = 18626;
const char *mqtt_user = "yqhwlaeu";
const char *mqtt_pass = "BtKtw3dGEMKQ";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido bajo el tópico ->");
  Serial.print(topic);
  Serial.print("\n");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  auxPatron = payload[0];
  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando Conexión MQTT");

    String clientId = "equipoAFFD";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conexión a MQTT exitosa");
      client.publish("salidaAFFD", "Primer mensaje");
      client.subscribe("patronAFFD");
    }
    else
    {
      Serial.print("Falló la conexión");
      Serial.print(client.state());
      Serial.println("Se intentará de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup_wifi()
{
  Serial.println();
  Serial.println("Conectando a...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectando a red ->");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

// apagar Todo
void apagarTodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], HIGH);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(filas[i], LOW);
  }
}

// prender todo
void turnEverythingOn()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], 0);
  }
  // turning on layers
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(filas[i], 1);
  }
}

// arriba abajo y viceversa
void arribaAbajo()
{
  int x = 75;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(filas[i], 0);
  }
  for (int y = 0; y < 5; y++)
  {
    for (int count = 0; count < 1; count++)
    {
      for (int i = 0; i < 4; i++)
      {
        digitalWrite(filas[i], 1);
        delay(x);
        digitalWrite(filas[i], 0);
      }
      for (int i = 4; i != 0; i--)
      {
        digitalWrite(filas[i - 1], 1);
        delay(x);
        digitalWrite(filas[i - 1], 0);
      }
    }
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(filas[i], 1);
      delay(x);
    }
    for (int i = 4; i != 0; i--)
    {
      digitalWrite(filas[i - 1], 0);
      delay(x);
    }
  }
}

// random rain
void randomRain()
{
  apagarTodo();
  int x = 100;
  for (int i = 0; i != 60; i += 2)
  {
    int randomColumn = random(0, 16);
    digitalWrite(columnas[randomColumn], 0);
    digitalWrite(filas[0], 1);
    delay(x + 50);
    digitalWrite(filas[0], 0);
    digitalWrite(filas[1], 1);
    delay(x);
    digitalWrite(filas[1], 0);
    digitalWrite(filas[2], 1);
    delay(x);
    digitalWrite(filas[2], 0);
    digitalWrite(filas[3], 1);
    delay(x + 50);
    digitalWrite(filas[3], 0);
    digitalWrite(columnas[randomColumn], 1);
  }
}

// prender y apagar lado a lado
void ladoALado()
{
  int x = 75;
  apagarTodo();
  // turn on layers
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(filas[i], 1);
  }
  for (int y = 0; y < 3; y++)
  {
    // turn on 0-3
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 4-7
    for (int i = 4; i < 8; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 8-11
    for (int i = 8; i < 12; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 12-15
    for (int i = 12; i < 16; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn off 0-3
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 4-7
    for (int i = 4; i < 8; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 8-11
    for (int i = 8; i < 12; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 12-15
    for (int i = 12; i < 16; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn on 12-15
    for (int i = 12; i < 16; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 8-11
    for (int i = 8; i < 12; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 4-7
    for (int i = 4; i < 8; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn on 0-3
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(columnas[i], 0);
      delay(x);
    }
    // turn off 12-15
    for (int i = 12; i < 16; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 8-11
    for (int i = 8; i < 12; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 4-7
    for (int i = 4; i < 8; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
    // turn off 0-3
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(columnas[i], 1);
      delay(x);
    }
  }
}

// spiral
void spiral()
{
  turnEverythingOn();
  int x = 60;
  for (int i = 0; i < 6; i++)
  {
    // spiral in clockwise
    digitalWrite(columnas[0], 1);
    delay(x);
    digitalWrite(columnas[1], 1);
    delay(x);
    digitalWrite(columnas[2], 1);
    delay(x);
    digitalWrite(columnas[3], 1);
    delay(x);
    digitalWrite(columnas[7], 1);
    delay(x);
    digitalWrite(columnas[11], 1);
    delay(x);
    digitalWrite(columnas[15], 1);
    delay(x);
    digitalWrite(columnas[14], 1);
    delay(x);
    digitalWrite(columnas[13], 1);
    delay(x);
    digitalWrite(columnas[12], 1);
    delay(x);
    digitalWrite(columnas[8], 1);
    delay(x);
    digitalWrite(columnas[4], 1);
    delay(x);
    digitalWrite(columnas[5], 1);
    delay(x);
    digitalWrite(columnas[6], 1);
    delay(x);
    digitalWrite(columnas[10], 1);
    delay(x);
    digitalWrite(columnas[9], 1);
    delay(x);
    // spiral out counter clockwise
    digitalWrite(columnas[9], 0);
    delay(x);
    digitalWrite(columnas[10], 0);
    delay(x);
    digitalWrite(columnas[6], 0);
    delay(x);
    digitalWrite(columnas[5], 0);
    delay(x);
    digitalWrite(columnas[4], 0);
    delay(x);
    digitalWrite(columnas[8], 0);
    delay(x);
    digitalWrite(columnas[12], 0);
    delay(x);
    digitalWrite(columnas[13], 0);
    delay(x);
    digitalWrite(columnas[14], 0);
    delay(x);
    digitalWrite(columnas[15], 0);
    delay(x);
    digitalWrite(columnas[11], 0);
    delay(x);
    digitalWrite(columnas[7], 0);
    delay(x);
    digitalWrite(columnas[3], 0);
    delay(x);
    digitalWrite(columnas[2], 0);
    delay(x);
    digitalWrite(columnas[1], 0);
    delay(x);
    digitalWrite(columnas[0], 0);
    delay(x);
    // spiral in counter clock wise
    digitalWrite(columnas[0], 1);
    delay(x);
    digitalWrite(columnas[4], 1);
    delay(x);
    digitalWrite(columnas[8], 1);
    delay(x);
    digitalWrite(columnas[12], 1);
    delay(x);
    digitalWrite(columnas[13], 1);
    delay(x);
    digitalWrite(columnas[14], 1);
    delay(x);
    digitalWrite(columnas[15], 1);
    delay(x);
    digitalWrite(columnas[11], 1);
    delay(x);
    digitalWrite(columnas[7], 1);
    delay(x);
    digitalWrite(columnas[3], 1);
    delay(x);
    digitalWrite(columnas[2], 1);
    delay(x);
    digitalWrite(columnas[1], 1);
    delay(x);
    digitalWrite(columnas[5], 1);
    delay(x);
    digitalWrite(columnas[9], 1);
    delay(x);
    digitalWrite(columnas[10], 1);
    delay(x);
    digitalWrite(columnas[6], 1);
    delay(x);
    // spiral out clock wise
    digitalWrite(columnas[6], 0);
    delay(x);
    digitalWrite(columnas[10], 0);
    delay(x);
    digitalWrite(columnas[9], 0);
    delay(x);
    digitalWrite(columnas[5], 0);
    delay(x);
    digitalWrite(columnas[1], 0);
    delay(x);
    digitalWrite(columnas[2], 0);
    delay(x);
    digitalWrite(columnas[3], 0);
    delay(x);
    digitalWrite(columnas[7], 0);
    delay(x);
    digitalWrite(columnas[11], 0);
    delay(x);
    digitalWrite(columnas[15], 0);
    delay(x);
    digitalWrite(columnas[14], 0);
    delay(x);
    digitalWrite(columnas[13], 0);
    delay(x);
    digitalWrite(columnas[12], 0);
    delay(x);
    digitalWrite(columnas[8], 0);
    delay(x);
    digitalWrite(columnas[4], 0);
    delay(x);
    digitalWrite(columnas[0], 0);
    delay(x);
  }
}

// parpadeo
void parpadeo()
{
  apagarTodo();
  int x = 10;
  for (int i = 0; i != 750; i += 2)
  {
    int randomFila = random(0, 4);
    int randomColumn = random(0, 16);

    digitalWrite(filas[randomFila], 1);
    digitalWrite(columnas[randomColumn], 0);
    delay(x);
    digitalWrite(filas[randomFila], 0);
    digitalWrite(columnas[randomColumn], 1);
    delay(x);
  }
}

// mostrar patron dependiente del numero
void despliegaPatron(char patron)
{
  switch (patron)
  {
  case '1':
    turnEverythingOn();
    break;
  case '2':
    arribaAbajo();
    break;
  case '3':
    randomRain();
    break;
  case '4':
    ladoALado();
    break;
  case '5':
    spiral();
    break;
  case '6':
    parpadeo();
    break;
  case '7':
    apagarTodo();
    break;
  default:
    apagarTodo();
    break;
  }
}

void setup()
{
  // put your setup code here, to run once:
  // pinMode(led_gpio, OUTPUT);
  Serial.begin(115200);

  for (int i = 0; i < 16; i++)
  {
    pinMode(columnas[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(filas[i], OUTPUT);
  }

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (client.connected() == false)
  {
    reconnect();
  }

  client.loop();
  despliegaPatron(auxPatron);
}
