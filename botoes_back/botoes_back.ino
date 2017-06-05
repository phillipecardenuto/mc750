const short  ledPin1 = 13;
const short  ledPin2 = 14;
const short  ledPin3 = 12;
const short  BotaoDaAlegria = 16;
const short  BotaoDaTristeza = 5;
const short  BotaoDoPrazer = 4;
short EstadoBotao1 = 0;
short  EstadoBotao2 = 0;
short  EstadoBotao3 = 0;
short  FlagBotao=0;

void setup(){
  pinMode(ledPin1, OUTPUT);
  pinMode(BotaoDaAlegria, INPUT);
  
  pinMode(ledPin2, OUTPUT);
  pinMode(BotaoDaTristeza, INPUT);
  
  pinMode(ledPin3, OUTPUT);
  pinMode(BotaoDoPrazer, INPUT);
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

}
void loop(){
  EstadoBotao1 = digitalRead(BotaoDaAlegria);
  EstadoBotao2 = digitalRead(BotaoDaTristeza);
  EstadoBotao3 = digitalRead(BotaoDoPrazer);
  if (EstadoBotao1 == HIGH and (FlagBotao==1 or FlagBotao==0)){
    alegria();
  }
  else if (EstadoBotao2 == HIGH and (FlagBotao==2 or FlagBotao==0) ){
    tristeza();
  }
  else if(EstadoBotao3 == HIGH and (FlagBotao==3 or FlagBotao==0) ){
    prazer();
  }
  else 
    FlagBotao=0;  
}
void alegria(){
  FlagBotao=1;
  digitalWrite(ledPin1, HIGH);
  delay(1000);
  digitalWrite(ledPin1, LOW);
}
void tristeza(){
  FlagBotao=2;
  digitalWrite(ledPin2, HIGH);
  delay(1000);
  digitalWrite(ledPin2, LOW);
}
void prazer(){
  FlagBotao=3;
  digitalWrite(ledPin3, HIGH);
  delay(1000);
  digitalWrite(ledPin3, LOW);
  
}
void desgosto(){
  
}
void raiva(){
  
}
void nojo(){
  
}


