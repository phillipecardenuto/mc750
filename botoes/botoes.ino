#include <Bounce2.h>
# define Intervalo 100


// Inicializa pinos dos Botoes
const short BotaoDaAlegria = 16; //D0
const short BotaoDaTristeza = 5; //D1
const short BotaoDoPrazer = 4; // D2
const short BotaoDaRaiva = 14; //D5
const short BotaoDoNojo = 12; //D6
const short BotaoDoDesgosto = 13; //D7

// Inicializa Debounce
Bounce b_alegria = Bounce ();
Bounce  b_tristeza = Bounce ();
Bounce  b_prazer = Bounce ();
Bounce  b_desgosto = Bounce ();
Bounce  b_raiva = Bounce ();
Bounce  b_nojo = Bounce ();

// Inicializa Estado dos Botoes
short EstadoBotaoDaAlegria = 0;
short EstadoBotaoDaTristeza = 0;
short EstadoBotaoDoPrazer = 0;
short EstadoBotaoDoDesgosto = 0;
short EstadoBotaoDaRaiva = 0;
short EstadoBotaoDoNojo = 0;

// Inicializa Flag
short FlagBotao=0;

void setup(){
  // Serial comunicação para a tela
  Serial.begin(9600);
  // Debug
  Serial.println("Comecando Teste:");
   
  // Inicializa os Botoes como entrada de porta
  pinMode(BotaoDaAlegria, INPUT);
  pinMode(BotaoDaTristeza, INPUT);
  pinMode(BotaoDoPrazer, INPUT);
  pinMode(BotaoDoDesgosto, INPUT);
  pinMode(BotaoDaRaiva, INPUT);
  pinMode(BotaoDoNojo, INPUT);

  // Configuram os botoes para o efeito de bounce
  b_alegria.attach(BotaoDaAlegria);
  b_alegria.interval(Intervalo);
  b_tristeza.attach(BotaoDaTristeza);
  b_tristeza.interval(Intervalo);
  b_prazer.attach(BotaoDoPrazer);
  b_prazer.interval(Intervalo);
  b_desgosto.attach(BotaoDoDesgosto);
  b_desgosto.interval(Intervalo);
  b_raiva.attach(BotaoDaRaiva);
  b_raiva.interval(Intervalo);
  b_nojo.attach(BotaoDoNojo);
  b_nojo.interval(Intervalo);
  // Começo da Comunicação
  Serial.println("+++\n+++\n+++");

}
void loop(){
  // Realiza o update do efeito de bounce
  b_alegria.update();
  b_tristeza.update();
  b_prazer.update();
  b_desgosto.update();
  b_raiva.update();
  b_nojo.update();
  
  // Verifica cada estado de botao 
  EstadoBotaoDaAlegria = b_alegria.read();
  EstadoBotaoDaTristeza = b_tristeza.read();
  EstadoBotaoDoPrazer = b_prazer.read();
  EstadoBotaoDoDesgosto = b_desgosto.read();
  EstadoBotaoDaRaiva = b_raiva.read();
  EstadoBotaoDoNojo = b_nojo.read();
  // Permite que um botao seja apertado de cada vez
  if (EstadoBotaoDaAlegria == HIGH and (FlagBotao==1 or FlagBotao==0)){
    alegria();
  }
  else if (EstadoBotaoDaTristeza == HIGH and (FlagBotao==2 or FlagBotao==0) ){
    tristeza();
  }
  else if(EstadoBotaoDoPrazer == HIGH and (FlagBotao==3 or FlagBotao==0) ){
    prazer();
  }
  else if(EstadoBotaoDoDesgosto == HIGH and (FlagBotao==4 or FlagBotao==0) ){
    desgosto();
  }
  else if(EstadoBotaoDaRaiva == HIGH and (FlagBotao==5 or FlagBotao==0) ){
    raiva();
  }
  else if(EstadoBotaoDoNojo == HIGH and (FlagBotao==6 or FlagBotao==0) ){
    nojo();
  }
  else 
    FlagBotao=0;  
   
}

// Funções de tratamento da ativação dos botões
void alegria(){
  if(FlagBotao != 1){
    Serial.println("=)");
    Serial.println("Alegria");
    delay(1000);
  }
  FlagBotao=1;
  
}
void tristeza(){
  if(FlagBotao != 2){
    Serial.println(":(");
    Serial.println("Tristeza");
    delay(1000);
  }
  FlagBotao=2;
  
}
void prazer(){
  if(FlagBotao != 3){
    Serial.println("xD");
    Serial.println("Prazer");
    delay(1000);
  }
  FlagBotao=3;
  
  
}
void desgosto(){
  if(FlagBotao != 4){
    Serial.println(":'(");
    Serial.println("Desgosto");
    delay(1000);
  }
  FlagBotao=4;
}
void raiva(){
  if(FlagBotao != 5){
    Serial.println(":@");
    Serial.println("Raiva");
    delay(1000);
  }
  FlagBotao=5;
  
}
void nojo(){
  if(FlagBotao != 6){
    Serial.println(":~/");
    Serial.println("Nojo");
    delay(1000);
  }
  FlagBotao=6;
  
}

