#include<Servo.h>
#include <ESP8266WiFi.h>
/**changes starts */
IPAddress staticIP832_150(192,168,79,15);
IPAddress gateway832_150(192,168,79,1);
IPAddress subnet832_150(255,255,255,0);
/**changes ends */

String  i;
WiFiServer server(80);

#define headLight 16
#define breakLight 5
#define mot1En 2
#define mot1For 0
#define mot1Back 4
#define mot2En 14
#define mot2For 13
#define mot2Back 12
Servo steer;
void setup() {
  // put your setup code here, to run once:
  pinMode(headLight,OUTPUT);
  pinMode(breakLight,OUTPUT);
  pinMode(mot1En,OUTPUT);
  pinMode(mot1For,OUTPUT);
  pinMode(mot1Back,OUTPUT);
  pinMode(mot2En,OUTPUT);
  pinMode(mot2For,OUTPUT);
  pinMode(mot2Back,OUTPUT);
  steer.attach(15);
  steer.write(90);
  digitalWrite(headLight,LOW);
  digitalWrite(breakLight,LOW);
  digitalWrite(mot1En,HIGH);
  digitalWrite(mot1For,LOW);
  digitalWrite(mot1Back,LOW);
  digitalWrite(mot2En,HIGH);
  digitalWrite(mot2For,LOW);
  digitalWrite(mot2Back,LOW);
  Serial.begin(9600);
 
  i = "";
  WiFi.disconnect();
  delay(1000);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Ready to Connect");
  WiFi.begin("MY SM-J7","12345678");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");
  }
  delay(1000); 
  /**changes starts */
  WiFi.config(staticIP832_150, gateway832_150, subnet832_150);
  /**changes ends */
  delay(1000);
  Serial.println("Connected to dlink");
  Serial.println("Local IP:");
  Serial.println((WiFi.localIP().toString()));
  Serial.println("Gateway IP");
  Serial.println((WiFi.gatewayIP().toString().c_str()));
  Serial.println("Host Name");
  Serial.println((WiFi.hostname()));
  server.begin();
  Serial.println("Goto: http://"+(WiFi.localIP().toString())+"/");
  
}

void loop() {
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    Serial.println(i);
    int command=i.toInt();
//     while(Serial.available()==0){
//       //Serial.println("...");  
//     }int command=0;
//     command=Serial.parseInt();
    Serial.println(command);
  switch(command){
    case 1:
      Serial.println("HeadLight on");
      digitalWrite(headLight,HIGH);
      delay(1000);
      break;
    case 2:
      Serial.println("HeadLight off");
      digitalWrite(headLight,LOW);
      delay(1000);
      break;
    case 3:
      Serial.println("Moving forward");
      digitalWrite(mot1For,HIGH);delay(1);
      digitalWrite(mot1Back,LOW);delay(1);
      digitalWrite(mot2For,HIGH);delay(1);
      digitalWrite(mot2Back,LOW);delay(1);
      break;
    case 4:
      Serial.println("Moving backward");
      digitalWrite(mot1For,LOW);delay(1);
      digitalWrite(mot1Back,HIGH);delay(1);
      digitalWrite(mot2For,LOW);delay(1);
      digitalWrite(mot2Back,HIGH);delay(1);
      break;
    case 5:
      Serial.println("Stoping car");
      digitalWrite(mot1For,LOW);delay(1);
      digitalWrite(mot1Back,LOW);delay(1);
      digitalWrite(mot2For,LOW);delay(1);
      digitalWrite(mot2Back,LOW);delay(1);
      Serial.println("BreakLight on");
      digitalWrite(breakLight,HIGH);
      delay(1000);
      Serial.println("BreakLight off");
      digitalWrite(breakLight,LOW);
      delay(1);
      break;
    case 6:
      Serial.println("Turning left");
      steer.write(65);
      delay(2000);
      steer.write(90);
      break;
    case 7:
      Serial.println("Turning right");
      steer.write(115);
      delay(2000);
      steer.write(90);
      break;
     case 8:
      setup();
    default:
      digitalWrite(headLight,LOW);
      digitalWrite(breakLight,LOW);
      digitalWrite(mot1En,HIGH);
      digitalWrite(mot1For,LOW);
      digitalWrite(mot1Back,LOW);
      digitalWrite(mot2En,HIGH);
      digitalWrite(mot2For,LOW);
      digitalWrite(mot2Back,LOW);
      break;
  }
  digitalWrite(4,HIGH);
  digitalWrite(D4,HIGH);
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("LED ON");
  client.println("</html>");
  delay(1);
}
