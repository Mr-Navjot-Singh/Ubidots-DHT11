//#include <UbidotsESPMQTT.h>

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-doDF1zc29HYZpUQsU2yH8JIG1ImQuy" // Your Ubidots TOKEN

#define WIFINAME "sukritid39" //Your SSID
#define WIFIPASS "deadbeefd39" // Your Wifi Pass

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTTYPE DHT11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// DHT Sensor
uint8_t DHTPin = D4;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE); 

float temperature, humidity;


// 10 seconds
long delayTime  = 1*60*1000;

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  
  pinMode(DHTPin, INPUT);
  dht.begin();  
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  
  }

void loop() {
  //For DHT11
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
    
  Serial.println("From DHT11 ---- ");
  Serial.print("Temperature : ");
  Serial.println(temperature);
  Serial.print("Humidity : ");
  Serial.println(humidity);
  Serial.println("\n");

  lcd.setCursor(0,0);
  lcd.print("Humidity : ");
  lcd.setCursor(11,0);
  lcd.print(humidity);
  lcd.setCursor(0,1);
  lcd.print("Temp : ");
  lcd.setCursor(7,1);
  lcd.print(temperature);


  
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
    
//  client.add("var1", 10.2); //Insert your variable Labels and the value to be sent
//  client.ubidotsPublish("NodeMCUSunand");
//  client.add("var2", 10.3);
//  client.ubidotsPublish("NodeMCUSunand");

//  client.add("temp1", temperature);
  client.add("sukriti_hum1", humidity);
  client.ubidotsPublish("NodeMCUSunand");
  client.add("sukriti_temp1", temperature);
  client.ubidotsPublish("NodeMCUSunand");

  
  client.loop();
  
  Serial.println("sleeping for some time before next send..");
  delay (delayTime);
  
  }
