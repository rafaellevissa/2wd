//bibliotecas:
//Modulo IRremote hx1838
#include <IRremote.h>
//servo motor 9g
#include <Servo.h>
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
//TimerFreeTone buzzer library
#include <TimerFreeTone.h>

//constantes:
#define SERVO 5 //servomotor 9g
//Ponte H L298N
//Motor direito 
#define motorPin1 11 // Entrada 1 do L293D
#define motorPin2 10 // Entrada 2 do L293D
//Motor esquerdo
#define motorPin3 9 // Entrada 3 do L293D
#define motorPin4 8 // Entrada 4 do L293D
//#define speedPin 6 // Pino de Ativação 1 do L293D - PORTA PWN
#define led 3 //Led farol
#define ledRE 13 //Led da ré
#define buzzer 12 //Buzina
//Define os pinos para o trigger e echo. Sonar
#define pino_trigger 6
#define pino_echo 7

//declaracao de variaveis:
int RECV_PIN = 4;//pino do modulo IRremote
int cont=0;
int sair=0;
int desligar=0;
//Controle remoto padrão
int BotaoFrente=0xFF10EF;
int BotaoMeio=0xFF38C7;
int BotaoBaixo=0xFF4AB5;
int BotaoEsquerda=0xFF18E7;
int BotaoDireita=0xFF5AA5;
int BotaoLed1=0xFF6897;
int BotaoLed0=0xFFB04F;
int BotaoBuzzer=0xFF9867;
int BotaoDesligar=0xFFA25D;
float cmMsec, inMsec; //Sonar
long microsec; //Sonar
int pos; // Posição Servo
Servo s; // Variável Servo

//declaracao das funcoes
void principal(int r);
void MenuCalibragem(); //calibra controle remoto
void inicializarRobo();
void GirarServo(); //servo 9g
void verificaObstaculo();//sonar verifica se ha obstaculo
//funcoes dos motores
void para(int Mspeed);
void frente(int Mspeed);
void traz(int Mspeed);
void direita(int Mspeed);
void esquerda(int Mspeed);

//Iniciando IR
IRrecv irrecv(RECV_PIN);
decode_results results;
//Inicializando Sonar nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicia o recebedor do IRremote
  // define os pinos da ponte para o arduino
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  //  pinMode(speedPin, OUTPUT);
  pinMode(led, OUTPUT);// LED farol
  pinMode(ledRE, OUTPUT);// LED Re
  pinMode(buzzer, OUTPUT);// Buzina
  pinMode(RECV_PIN, INPUT);// IR
  s.attach(SERVO); //inicializa o pino do servo
  inicializarRobo();
  MenuCalibragem(); 
}
void loop(){
  GirarServo();
  if (irrecv.decode(&results)){
    int r= (results.value);
    principal(r);// chama a função principal
    irrecv.resume(); // recebe o próximo valor
  } 
}

//funcoes:
void verificaObstaculo(){
  microsec = ultrasonic.timing(); //sonar
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); //sonar
  if (cmMsec<20){
    para(0);
    traz(1023);
    delay(300);
    para(0);
    for(int i=0;i<2;i++){
      digitalWrite(led, HIGH);
      digitalWrite(ledRE, HIGH);
      delay (1000);
      digitalWrite(led, LOW);
      digitalWrite(ledRE, LOW);
      TimerFreeTone(buzzer,660,100);
      delay(150);
      TimerFreeTone(buzzer,660,100);
      delay(300);
      TimerFreeTone(buzzer,660,100);
      delay(150);
      TimerFreeTone(buzzer,660,100);
      delay(300);
    } 
  }
}

void GirarServo(){ //Gira a cabeca do robo com o servo e a cada posicao, verifica distancia do obstaculo (sonar)
  if(desligar==0){
    verificaObstaculo();
    for(pos = 0; pos < 180; pos++)
    {
      s.write(pos); //Servo
      delay(1);
    }
    delay(5);
    verificaObstaculo();
    for(pos = 180; pos >= 0; pos--)
    {
      s.write(pos); //servo
      delay(1);    
    }
    verificaObstaculo();
  }
}

void inicializarRobo(){ //Etapas de inicializacao para testar os componentes
  s.write(0); // Inicia motor posição zero
  digitalWrite(led, HIGH);
  digitalWrite(ledRE, HIGH);
  delay(500); 
  TimerFreeTone(buzzer,660,100);
  delay(150);
  TimerFreeTone(buzzer,660,100);
  delay(300);
  TimerFreeTone(buzzer,660,100);
  delay(150);
  TimerFreeTone(buzzer,660,100);
  delay(300);
  digitalWrite(led, LOW);
  digitalWrite(ledRE, LOW);
  //servo motor 9g
  for(pos = 0; pos < 180; pos++)
  {
    s.write(pos);
    delay(5);
  }
  delay(500);
  for(pos = 180; pos >= 90; pos--)
  {
    s.write(pos);
    delay(5);
  }
  frente(1023);
  delay(100);
  para(0);
  delay(100);
  traz(1023);
  delay(100);
  para(0);
}

void MenuCalibragem(){
  //while((Serial.available()>0)&&(sair==0)) {
  while(sair==0){
    TimerFreeTone(buzzer,660,100);
    delay(150);
    //int entrada =Serial.read();
    //if((entrada=='s') || (entrada=='S')){
      cont=0;
      Serial.println("Aperte o botão para frente");
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoFrente= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para ré");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoBaixo= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para freiar");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoMeio= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para esquerda");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoEsquerda= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para direita");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoDireita= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para ligar farol");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoLed1= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para desligar farol");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoLed0= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para desligar o carro");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoDesligar= (results.value);
          cont++;
        }
      }
      TimerFreeTone(buzzer,660,100);
      delay(150);
      cont=0;
      delay(300);
      Serial.println("Aperte o botão para buzinar");
      irrecv.resume(); // recebe o próximo valor
      while (cont==0){
        if (irrecv.decode(&results)){
          Serial.println(results.value, HEX);
          BotaoBuzzer= (results.value);
          cont++;
          sair++;
        }
      }                   
  }
  TimerFreeTone(buzzer,660,100);
  delay(150);
  TimerFreeTone(buzzer,660,100);
  delay(150);
  TimerFreeTone(buzzer,660,100);
  delay(150);
  Serial.println("Iniciando robô...");
}

void principal(int r){
  if(r==BotaoFrente){ //frente  
    frente(1023);//chama a função e indica a velocidade entre parêntese 
  } 
  if(r==BotaoMeio){ //meio
    para(0);//chama a função e indica a velocidade entre parêntese
  }
  if(r==BotaoBaixo){ //Seta baixo
    traz(1023);//chama a função e indica a velocidade entre parêntese   
  }
  if(r==BotaoEsquerda){ //seta esquerda
    esquerda(1023);//chama a função e indica a velocidade entre parêntese
  }
  if(r==BotaoDireita){ //seta direita
    direita(1023);//chama a função e indica a velocidade entre parêntese
  }
  if(r==BotaoLed1){ //1
    digitalWrite(led, HIGH);//liga o LEB branco (farol)
  }
  if(r==BotaoLed0){ //2
    digitalWrite(led, LOW);//desliga o LEB branco (farol)
  }
  if(r==BotaoBuzzer){ //buzina
    TimerFreeTone(buzzer,660,100);
    delay(150);
    TimerFreeTone(buzzer,660,100);
    delay(300);
  }
  if(r==BotaoDesligar){
    if(desligar==0){
      desligar=1;
      para(0);
      digitalWrite(led, LOW);//desliga o LEB branco (farol)
      digitalWrite(ledRE, LOW);//desliga o LEB branco (farol)
    }else{
      desligar=0;
    }
  }
  
}

void para(int Mspeed){ // Uma variável para armazenar o valor de velocidade atual 
  //analogWrite(speedPin, Mspeed); // escreve a velocidade para o pino de Ativação 1
  //Motor direito
  digitalWrite(ledRE, HIGH);
  digitalWrite(motorPin1, LOW); // define a Entrada 1 do L293D como baixa
  digitalWrite(motorPin2, LOW); // define a Entrada 2 do L293D como alta
  //Motor esquerdo
  digitalWrite(motorPin3, LOW); // define a Entrada 3 do L293D como baixa
  digitalWrite(motorPin4, LOW); // define a Entrada 4 do L293D como alta 
  
 }

void esquerda(int Mspeed){ // Uma variável para armazenar o valor de velocidade atual 
  // analogWrite(speedPin, Mspeed); // escreve a velocidade para o pino de Ativação 1
  //Motor direito
  digitalWrite(ledRE, LOW);
  digitalWrite(motorPin1, HIGH); // define a Entrada 1 do L293D como baixa
  digitalWrite(motorPin2, LOW); // define a Entrada 2 do L293D como alta
  //Motor esquerdo
  digitalWrite(motorPin3, LOW); // define a Entrada 3 do L293D como baixa
  digitalWrite(motorPin4, HIGH); // define a Entrada 4 do L293D como alta 
 }

void direita(int Mspeed){
  //analogWrite(speedPin, Mspeed); // escreve a velocidade para o pino de Ativação 1
  //Motor direito
  digitalWrite(ledRE, LOW);
  digitalWrite(motorPin1, LOW); // define a Entrada 1 do L293D como baixa
  digitalWrite(motorPin2, HIGH); // define a Entrada 2 do L293D como alta
  //Motor esquerdo
  digitalWrite(motorPin3, HIGH); // define a Entrada 3 do L293D como baixa
  digitalWrite(motorPin4, LOW); // define a Entrada 4 do L293D como alta
 }

void traz(int Mspeed){
  //analogWrite(speedPin, Mspeed); // escreve a velocidade para o pino de Ativação 1
  //Motor direito
  digitalWrite(ledRE, HIGH);
  digitalWrite(motorPin1, LOW); // define a Entrada 1 do L293D como baixa
  digitalWrite(motorPin2, HIGH); // define a Entrada 2 do L293D como alta
  //Motor esquerdo
  digitalWrite(motorPin3, LOW); // define a Entrada 3 do L293D como baixa
  digitalWrite(motorPin4, HIGH); // define a Entrada 4 do L293D como alta
}

void frente(int Mspeed){
  //analogWrite(speedPin, Mspeed); // escreve a velocidade para o pino de Ativação 1
  //Motor direito
  digitalWrite(ledRE, LOW);
  digitalWrite(motorPin1, HIGH); // define a Entrada 1 do L293D como baixa
  digitalWrite(motorPin2, LOW); // define a Entrada 2 do L293D como alta
  //Motor esquerdo
  digitalWrite(motorPin3, HIGH); // define a Entrada 3 do L293D como baixa
  digitalWrite(motorPin4, LOW); // define a Entrada 4 do L293D como alta
 }
