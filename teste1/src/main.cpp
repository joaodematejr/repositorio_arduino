#include <Arduino.h>

void setup()
{
  //BUILTIN_LED = GPIO2 DO ESP8266
  pinMode(BUILTIN_LED, OUTPUT); //DEFINE O PINO COMO SAÍDA
}

void loop()
{
  digitalWrite(BUILTIN_LED, LOW);  //LED DA PLACA ACENDE (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(9000);                     //INTERVALO DE 1 SEGUNDO
  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000);                     //INTERVALO DE 1 SEGUNDO
}