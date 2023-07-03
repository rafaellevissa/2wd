# robo-2wd-controleIR

Biblioteca IR (IRremote(https://github.com/z3t0/Arduino-IRremote)
Biblioteca FreeTone (https://bitbucket.org/teckel12/arduino-timer-free-tone/downloads/)
Biblioteca Sonar HC-SR04 (https://github.com/filipeflop/Ultrasonic)

Há conflitos entre as bibliotecas, servo, tone e IRremote. Por isso utilizamos a biblioteca FreeTone.

Caso haja algum conflito basta abrir o diretório do usuário, arduino, bibliotecas (libraries), abra a pasta da biblioteca IRremote e altere as linhas do arquivo IRremoteInt
Basta alternar os comentários do timer1 e timer2


#else
  //#define IR_USE_TIMER1   // tx = pin 9
  #define IR_USE_TIMER2     // tx = pin 3
  
  
  
Montagem do robô 2WD arduino.
Material:
2 Chassis carro robô MDF (https://produto.mercadolivre.com.br/MLB-715187884-placa-acrilica-pra-chassi-carro-robot-arduino-wifi-nodemcu-_JM)
2 rodas 68mm (https://www.filipeflop.com/produto/roda-68mm-para-chassi-robo-robotica/)
2 motores DC (3-6V) (https://www.filipeflop.com/produto/motor-dc-3-6v-com-caixa-de-reducao-e-eixo-duplo/)
1 Roda de apoio silicone 35mm (https://produto.mercadolivre.com.br/MLB-901245154-30-rodizio-gel-silicone-giratorio-rodinha-roda-35mm-strava-_JM)
1 kit de parafusos, porcas, arruelas
1 Ponte H L298N (https://www.filipeflop.com/produto/driver-motor-ponte-h-l298n/)
1 kit de jumpers M-M, M-F, F-F
2 Leds Vermelhos 5mm (https://www.filipeflop.com/produto/led-difuso-5mm-vermelho-x10-unidades/)
2 leds Amarelos 5mm alto brilho (https://www.filipeflop.com/produto/led-alto-brilho-5mm-amarelo-x5-unidades/)
1 suporte de bateria AA x6 (https://produto.mercadolivre.com.br/MLB-825064519-suporte-porta-6-pilhas-aa-com-plug-p4-fonte-p-arduino-_JM)
6 baterias AA
1 Buzzer 5V (https://www.filipeflop.com/produto/buzzer-ativo-5v/)
1 protoboard 170 pinos (https://produto.mercadolivre.com.br/MLB-737285872-mini-protoboard-170-pinos-para-arduino-ou-pic-_JM)
1 Arduino Uno R3 (https://www.filipeflop.com/produto/placa-uno-r3-cabo-usb-para-arduino/)
1 Sensor shield V4 (https://www.filipeflop.com/produto/sensor-shield-v4-0-para-arduino/)
1 kit Controle IR (https://www.filipeflop.com/produto/kit-controle-remoto-ir/)
1 sensor sonar HC-SR04 (https://www.filipeflop.com/produto/sensor-de-distancia-ultrassonico-hc-sr04/)
1 servomotor 9g SG90 Tower Pro (https://www.filipeflop.com/produto/micro-servo-9g-sg90-towerpro/)
1 Suporte Servo Motor 9g (https://produto.mercadolivre.com.br/MLB-739794277-suporte-pan-tilt-p-cmera-fpv-motores-micro-servo-arduino-_JM)

Material para Procedimento:
Estação de Solda
Estanho
Pistola cola quente
Chaves Fenda, Estrela
Alicates, bico e corte

Orientações da montagem: https://docs.google.com/presentation/d/138mVDRlrBp1LDkDLbX2-x2LB33xj4Wb_qsU8e4eOa2s/edit?usp=sharing

Códigos dos sensores separados:
Ponte H L298N: https://www.filipeflop.com/blog/motor-dc-arduino-ponte-h-l298n/
Sonar: https://www.filipeflop.com/blog/sensor-ultrassonico-hc-sr04-ao-arduino/
Servomotor 9g: https://www.filipeflop.com/blog/micro-servo-motor-9g-sg90-com-arduino-uno/
Controle IR: https://www.arduinoecia.com.br/2013/09/controle-remoto-ir-no-arduino.html
