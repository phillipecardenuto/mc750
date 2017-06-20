#include <Bounce2.h>
#include <    .h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

# define Intervalo 100

//WiFI
#define WIFI_SSID       "PENSIONATO VIVO DIAN"
#define WIFI_PASS       "2462462016"

//Adafruit IO
#define AIO_SERVER       "io.adafruit.com"
#define AIO_SERVERPORT   1883
#define AIO_USERNAME     "R0m3r0"
#define AIO_KEY          "b7b62e5209d84092b25e4ae48598ea29"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish image = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/image");

void MQTT_connect();

// Inicializa pinos dos Botoes
const short BotaoDaAlegria = 16; //D0   //espoja
const short BotaoDaTristeza = 14; //D5  //Tristeza
const short BotaoDoFelicia = 12; // D6  //ALGODAO
const short BotaoDaRaiva = 4; //D2      //LIXA
const short BotaoDoNojo = 13; //D7       //amoeba
const short BotaoDoDesgosto = 5; //D1  // VELUDO AMOR


//ALEGRIA - ESPONJA
//AMOR - VELUDO
//DESGOSTO - AMOEBA
//FELICIA - ALGODAO
//RAIVA- LIXA
//TRISTEZA - VELCRO


// Inicializa Debounce
Bounce b_alegria = Bounce ();
Bounce  b_tristeza = Bounce ();
Bounce  b_felicia = Bounce ();
Bounce  b_desgosto = Bounce ();
Bounce  b_raiva = Bounce ();
Bounce  b_nojo = Bounce ();

// Inicializa Estado dos Botoes
short EstadoBotaoDaAlegria = 0;
short EstadoBotaoDaTristeza = 0;
short EstadoBotaoDoFelicia = 0;
short EstadoBotaoDoDesgosto = 0;
short EstadoBotaoDaRaiva = 0;
short EstadoBotaoDoNojo = 0;

// Inicializa Flag
short FlagBotao = 0;

void setup() {
  // Serial comunicação para a tela
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



  // Inicializa os Botoes como entrada de porta
  pinMode(BotaoDaAlegria, INPUT);
  pinMode(BotaoDaTristeza, INPUT);
  pinMode(BotaoDoFelicia, INPUT);
  pinMode(BotaoDoDesgosto, INPUT);
  pinMode(BotaoDaRaiva, INPUT);
  pinMode(BotaoDoNojo, INPUT);

  // Configuram os botoes para o efeito de bounce
  b_alegria.attach(BotaoDaAlegria);
  b_alegria.interval(Intervalo);
  b_tristeza.attach(BotaoDaTristeza);
  b_tristeza.interval(Intervalo);
  b_felicia.attach(BotaoDoFelicia);
  b_felicia.interval(Intervalo);
  b_desgosto.attach(BotaoDoDesgosto);
  b_desgosto.interval(Intervalo);
  b_raiva.attach(BotaoDaRaiva);
  b_raiva.interval(Intervalo);
  b_nojo.attach(BotaoDoNojo);
  b_nojo.interval(Intervalo);
  // Começo da Comunicação
  Serial.println("+++\n+++\n+++");

}
void loop() {
  MQTT_connect();
  // Realiza o update do efeito de bounce
  b_alegria.update();
  b_tristeza.update();
  b_felicia.update();
  b_desgosto.update();
  b_raiva.update();
  b_nojo.update();

  // Verifica cada estado de botao
  EstadoBotaoDaAlegria = b_alegria.read();
  EstadoBotaoDaTristeza = b_tristeza.read();
  EstadoBotaoDoFelicia = b_felicia.read();
  EstadoBotaoDoDesgosto = b_desgosto.read();
  EstadoBotaoDaRaiva = b_raiva.read();
  EstadoBotaoDoNojo = b_nojo.read();
  // Permite que um botao seja apertado de cada vez
  if (EstadoBotaoDaAlegria == HIGH and (FlagBotao == 1 or FlagBotao == 0)) {
    alegria();
  }
  else if (EstadoBotaoDaTristeza == HIGH and (FlagBotao == 2 or FlagBotao == 0) ) {
    tristeza();
  }
  else if (EstadoBotaoDoFelicia == HIGH and (FlagBotao == 3 or FlagBotao == 0) ) {
    felicia();
  }
  else if (EstadoBotaoDoDesgosto == HIGH and (FlagBotao == 4 or FlagBotao == 0) ) {
    desgosto();
  }
  else if (EstadoBotaoDaRaiva == HIGH and (FlagBotao == 5 or FlagBotao == 0) ) {
    raiva();
  }
  else if (EstadoBotaoDoNojo == HIGH and (FlagBotao == 6 or FlagBotao == 0) ) {
    nojo();
  }
  else
    FlagBotao = 0;

}


/*
   Para Cada função é preciso fazer um publish quando o botao eh acionado para o feed do nome do botao
   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
   X----------------ARRUMAR--------------------X
   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/





// Funções de tratamento da ativação dos botões
void alegria() {
  if (FlagBotao != 1) {
    Serial.println("=)");
    Serial.println("Alegria");
    image.publish(3);
    delay(1000);
  }
  FlagBotao = 1;

}
void tristeza() {
  if (FlagBotao != 2) {
    Serial.println(":(");
    Serial.println("Tristeza");
    image.publish(1);
    delay(1000);
  }
  FlagBotao = 2;

}
//Felica
void felicia() {
  if (FlagBotao != 3) {
    Serial.println("xD");
    Serial.println("Felicia");
    delay(1000);
    image.publish(2);
  }
  FlagBotao = 3;


}


void desgosto() {
  if (FlagBotao != 4) {
    Serial.println(":'(");
    Serial.println("Desgosto");
    delay(1000);
    image.publish(6);
  }
  FlagBotao = 4;
}
void raiva() {
  if (FlagBotao != 5) {
    Serial.println(":@");
    Serial.println("Raiva");
    delay(1000);
    image.publish(5);
  }
  FlagBotao = 5;

}

//Amor
void nojo() {
  if (FlagBotao != 6) {
    Serial.println(":~/");
    Serial.println("Nojo");
    delay(1000);
    image.publish(4);
  }
  FlagBotao = 6;

}

void MQTT_connect()
{
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

