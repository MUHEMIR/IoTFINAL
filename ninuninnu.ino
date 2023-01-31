#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//#define FIREBASE_HOST "iot-firebase-kelompok3-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "uvI2VxdMxreX0BjGCr7aGV5es5Iom5Ccf4F0sgUT"
//SHA-1 FINGERPRINT yg digunakan --> 04:E0:BD:B0:F8:63:22:3C:3A:19:7D:92:B6:79:2A:44:BF:77:FC:DA

//#define FIREBASE_HOST "iot-firebase-esp-01-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "GyutJokDbDr2WyFZpLryQlvuRD2KPyHB90bvzglj"

#define WIFI_SSID "MiniPEKZ"
#define WIFI_PASSWORD "RoyalAirforce"

#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
void setup(void)
{ 
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  delay(1000);
  
  //connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  //connect to wifi.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop() {
    Firebase.setString("Muhammad-Emir-Ghiffari/NIM","2101221013");
    float h = dht.readHumidity();
    Firebase.setFloat("Muhammad-Emir-Ghiffari/HUMIDITY",h);
    float t = dht.readTemperature();
    Firebase.setFloat("Ivan-Saputra-Zebua/TEMPERATURE",t);         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    if (Firebase.failed()){
    Serial.print("pushing /temperature failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(2000);
}
