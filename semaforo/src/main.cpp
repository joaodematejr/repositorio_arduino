#include <ESP8266WiFi.h>

const char *ssid = "João 300 MB";
const char *password = "minha senha";

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  delay(10);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  Serial.println();
  Serial.println();
  Serial.print("Conectando a rede ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  server.begin();
  Serial.println("Servidor Iniciado");

  Serial.print("Usar essa URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Aguardando");
  while (!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value = LOW;
  if (request.indexOf("/LUZ=LIGADA") != -1)
  {
    digitalWrite(BUILTIN_LED, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LUZ=DESLIGADA") != -1)
  {
    digitalWrite(BUILTIN_LED, LOW);
    value = LOW;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Status da Luz: ");
  if (value == HIGH)
  {
    client.print("LIGADA");
  }
  else
  {
    client.print("DESLIGADA");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LUZ=LIGADA\">Aqui</a> Desativar Luz LIGADA<br>");
  client.println("Click <a href=\"/LUZ=DESLIGADA\">Aqui</a>Ativar Luz DESLIGADA<br>");
  client.println("</html>");
  delay(1);
  Serial.println("Usuário saiu (: ");
  Serial.println("");
}
