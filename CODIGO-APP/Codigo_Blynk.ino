String str,aux;
int data,caso,h,t,moisture_percentage,lux;
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "SKU2xY8H-PJb7GEbaotqfhI2C3DJ4LVx";
char ssid[] = "Totalplay-3C9C";
char pass[] = "3C9C4A10359brmm4";

BlynkTimer timer;

void setup()
{
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
   timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
   if (Serial.available() > 0)
   {
    str = Serial.readStringUntil('\n');
    caso = str.toInt();
switch (caso) {
  case -5:
    aux = Serial.readStringUntil('\n');
    h = aux.toInt();
    Serial.print("La humedad es: ");
    Serial.println(h);
    break;
  case -4:
    aux = Serial.readStringUntil('\n');
    t = aux.toInt();
    Serial.print("La temperatura es: ");
    Serial.println(t);
    break;
    case -3:
    aux = Serial.readStringUntil('\n');
    lux = aux.toInt();
    Serial.print("Lux: ");
    Serial.println(lux);
    break;
    case -2:
    aux = Serial.readStringUntil('\n');
    moisture_percentage = aux.toInt();
    Serial.print("La humedad de la tierra es: ");
    Serial.println(moisture_percentage);
    break;
    
  default:
   
    break;
}

   }
}

void sendSensor()
{

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, moisture_percentage);
  Blynk.virtualWrite(V8, lux);
}
