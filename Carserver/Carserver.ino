#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "CarServer";  
const char* password = "1234567810";

// IPAddress local_ip(192,168,1,38);
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

int m1 = D1;
int m2 = D2;
int m3 = D3;
int m4 = D4;
String currcmd = ""; 
void move_left();
void move_forward();
void move_backward();
void move_right();
void stop();

void setup() {

  Serial.begin(9600);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");

  server.on("/",handle_command);
  server.begin();

  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);  

}

void loop() {
  server.handleClient();

}
void handle_command(){
  
  Serial.println(server.args());
  String cmd = server.arg("cmd");
  Serial.println(server.arg("cmd"));
  if(cmd == "left" && currcmd != cmd){
    currcmd = cmd;
    Serial.println(currcmd);
    move_left();
  }
  else if(cmd == "right"  && currcmd != cmd){
    currcmd = cmd;
    Serial.println(currcmd);
    move_right();
  }
  else if(cmd == "forward" && currcmd != cmd){
    currcmd = cmd;
    Serial.println(currcmd);
    move_forward();
  }
  else if(cmd == "backward" && currcmd != cmd){
    currcmd = cmd;
    Serial.println(currcmd);
    move_backward();
  } 
  else if(cmd == "stop" && currcmd != cmd){
    currcmd = cmd;
    Serial.println(currcmd);
    stop();
  }
  server.send(200,"text/plain","ok");
}

void move_forward(){
  digitalWrite(m1,1);
  digitalWrite(m2,0);
  digitalWrite(m3,1);
  digitalWrite(m4,0);
  delay(100);  
}
void move_backward(){
  digitalWrite(m1,0);
  digitalWrite(m2,1);
  digitalWrite(m3,0);
  digitalWrite(m4,1);
  delay(100);
}

void move_left(){
  digitalWrite(m1,1);
  digitalWrite(m2,0);
  digitalWrite(m3,0);
  digitalWrite(m4,1);
  delay(100);
}

void move_right(){
  digitalWrite(m1,0);
  digitalWrite(m2,1);
  digitalWrite(m3,1);
  digitalWrite(m4,0);
  delay(100);
}
void stop(){
  digitalWrite(m1,0);
  digitalWrite(m2,0);
  digitalWrite(m3,0);
  digitalWrite(m4,0);
  delay(100);
}