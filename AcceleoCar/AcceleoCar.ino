#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define Height 32
#define Width 128
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(Width, Height, &Wire, -1);
Adafruit_ADXL345_Unified mpu = Adafruit_ADXL345_Unified();
//const char* ssid = "CarServer";  // Enter SSID here
//const char* password = "1234567810";  //Enter Password here
const char* ssid = "Samsung";  // Enter SSID here
const char* password = "kapil8279";  //Enter Password here
String base = "http://192.168.4.1/";
WiFiClient client;
HTTPClient http;
String currcmd = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mpu.begin();
  if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println("Display Start");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Initiating...");
    display.display();
    delay(2000);
  }
  WiFi.begin(ssid,password);
  Serial.println("Connecting");
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Connecting ....");
  display.display();
  while(WiFi.status() != WL_CONNECTED) {
    yield();
  }
  Serial.println("Connected");
  display.setCursor(0,0);
  display.println("Connected");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  if(WiFi.status() == WL_CONNECTED){
    display.setCursor(0,0);
    display.println("Connected");
    sensors_event_t a, g, temp;
    mpu.getEvent(&a);

    /* Print out the values */
    float x = a.gyro.x;
    float y = a.gyro.y;
    //display.setCursor(1,0);
    
    
    String cmd = getCMD(x, y);
    if(currcmd != cmd){
      String serverPath = base+"?cmd=" + cmd;
      http.begin(client, serverPath.c_str());
      int res = http.GET();
      Serial.println(res);
      currcmd = cmd;
    }
    
  }
  else{
    display.setCursor(0,0);
    display.println("Disconnected");
  }
  display.display();
	delay(50);
}

String getCMD(float x,float y){
  if(y > 5.0){
    return "backward";
  }
  else if(y < -5.0){
    return "forward";
  }
  else if(x > 5.0){
    return "right";
  }
  else if(x < -5.0){
    return "left";
  }
  else {
    return "stop";
  }
}
