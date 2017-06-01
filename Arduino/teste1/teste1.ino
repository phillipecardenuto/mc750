// Daremos um nome ao pino que ficara o LED:
const int led = 16;
const int botton =5 ;

void interrupcao(){
  digitalWrite(led, HIGH); // Liga o LED (HIGH = nível lógico alto)
  delay(10000);
  loop();
 
}
 
// Esta função "setup" roda uma vez quando a placa e ligada ou resetada
void setup() {
  pinMode(led, OUTPUT); // Configura o pino do led (digital) como saída
  attachInterrupt(botton,interrupcao,RISING); //Configurando a interrupção
}
 
// Função que se repete infinitamente quando a placa é ligada
void loop() {
  digitalWrite(led, HIGH); // Liga o LED (HIGH = nível lógico alto)
  delay(1000);             // Espera um segundo
  digitalWrite(led, LOW);  // Desliga o LED (LOW = nível lógico baixo)
  delay(1000);             // Espera um segundo
}
