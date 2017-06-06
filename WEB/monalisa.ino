#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const int led_pin = 16;
const int vibration_pin = 5;
int vibration_last = 0;

//WiFI
#define WIFI_SSID       "INSIRA AQUI O NOME DA REDE WI-FI"
#define WIFI_PASS       "INSIRA AQUI A SENHA DA REDE WI-FI"

//Adafruit IO
#define AIO_SERVER       "io.adafruit.com"
#define AIO_SERVERPORT   1883
#define AIO_USERNAME     "INSIRA SEU USERNAME AQUI"
#define AIO_KEY          "INSIRA SUA AIO KEY AQUI"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish vibration = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/vibration");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");
void MQTT_connect();

void setup()
{
  pinMode(led_pin, OUTPUT);
  
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&led);
}

void loop()
{
  MQTT_connect();

  if(digitalRead(vibration_pin) == HIGH && vibration_last == 0)
  {
    vibration.publish(1);
    Serial.println("Vibration HIGH");
    vibration_last = 1;
    delay(300);
  }

  if(digitalRead(vibration_pin) == LOW && vibration_last == 1)
  {
    vibration.publish(0);
    Serial.println("Vibration LOW");
    vibration_last = 0;
    delay(300);
  }

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(100)))
  {
    if (subscription == &led)
    {
      Serial.print("led: ");
      Serial.println((char *)led.lastread);
      if (strcmp((char *)led.lastread, "1") == 0)
      {
        digitalWrite(led_pin, HIGH);
      }
      if (strcmp((char *)led.lastread, "0") == 0)
      {
        digitalWrite(led_pin, LOW);
      }
    }
  }
  
}

void MQTT_connect()
{
  int8_t ret;

  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)
  {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0)
       {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
