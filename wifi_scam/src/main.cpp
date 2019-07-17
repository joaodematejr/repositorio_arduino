#include <ESP8266WiFi.h>
#define SERIAL_BAUD 9600
#define WIFI_DELAY 500
#define MAX_SSID_LEN 32
#define MAX_CONNECT_TIME 30000
char ssid[MAX_SSID_LEN] = "";
void scanAndSort()
{
  memset(ssid, 0, MAX_SSID_LEN);
  int n = WiFi.scanNetworks();
  Serial.println("Scan completado !!!");
  if (n == 0)
  {
    Serial.println("Não foi possivel Encontrar Redes WIFI");
  }
  else
  {
    Serial.print(n);
    Serial.println(" Redes Encontradas.");
    int indices[n];
    for (int i = 0; i < n; i++)
    {
      indices[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
        {
          std::swap(indices[i], indices[j]);
        }
      }
    }
    for (int i = 0; i < n; ++i)
    {
      Serial.println("A rede Sem Senha e  mais forte é:");
      Serial.print(WiFi.SSID(indices[i]));
      Serial.print(" ");
      Serial.print(WiFi.RSSI(indices[i]));
      Serial.print(" ");
      Serial.print(WiFi.encryptionType(indices[i]));
      Serial.println();
      if (WiFi.encryptionType(indices[i]) == ENC_TYPE_NONE)
      {
        memset(ssid, 0, MAX_SSID_LEN);
        strncpy(ssid, WiFi.SSID(indices[i]).c_str(), MAX_SSID_LEN);
        break;
      }
    }
  }
}

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Serial.println("Verificando redes sem Senhas ...");
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(WIFI_DELAY);
    scanAndSort();
    delay(WIFI_DELAY);
    if (strlen(ssid) > 0)
    {
      Serial.print("Conectando na Rede ...");
      Serial.println(ssid);
      WiFi.begin(ssid);
      unsigned short try_cnt = 0;
      while (WiFi.status() != WL_CONNECTED && try_cnt < MAX_CONNECT_TIME / WIFI_DELAY)
      {
        delay(WIFI_DELAY);
        Serial.print(".");
        try_cnt++;
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println("");
        Serial.println("Conexão realizada com Sucesso !!!");
        Serial.println("O endereço IP do seu dispositivo é ");
        Serial.println(WiFi.localIP());
      }
      else
      {
        Serial.println("Conexão Falhou");
      }
    }
    else
    {
      Serial.println("Nenhuma rede aberta disponível. :-(");
    }
  }
}

void loop()
{
}