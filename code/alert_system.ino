//key alert system
//find your devices ;keys/wallet when you misplace them just by a click of a button
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 

ESP8266WebServer server(80);   
const int buz_pin = 4;

char ssid[] = "NEVEREST";//wifi name
char pass[] = "nikoworks";//wifi password

//the docfile for the web page created
//contains a button that you can click to get the location of your keys

String html_code = "<!DOCTYPE html><html><head><style>.button {border: none;padding: 12px 40px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}.button1 {background-color: black; color: white; border: 3px solid #1c1c1b;border-radius: 30px}body {text-align: center;}</style></head><body><h2>Smart Keychain</h2><br><p><li>Press the Button to locate your keys</li></p><br><br><li>Once you locate them,press it again to turn off the buzzer</li><br><br><form action=\"/BUZ\" method=\"POST\"><button class=\"button button1\">FIND KEYS!!</button></form><br><br>";
boolean buzzing_state = false;

//access the web page
void handleRoot() { 
server.send(200, "text/html", html_code + "Current state: <b>" + buzzing_state);//ecxecuted when we open the webpage in  the browser using the nodemcu address.Sends the current state of the buzzer and the webpage will toggle a button to the webbserver.
}

//used to change the buzzing state when the button is pressed in the webpage
void handleBUZ() { 
buzzing_state = !buzzing_state; //if buzzing state is true
server.sendHeader("Location","/"); //send location
server.send(303); 
}

void handleNotFound(){
server.send(404, "text/plain", "404: Not found"); //webpage not found
}

void setup(void){ 
  Serial.begin(115200);        
  delay(10);
  pinMode(buz_pin, OUTPUT);
    pinMode(buz_pin, OUTPUT);
      pinMode(buz_pin, OUTPUT);
  //wifi connection
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {    
    delay(500);
  }
  Serial.println("OK!");
  Serial.print("IP address: ");//sends network ip address
  Serial.println(WiFi.localIP());           
  Serial.println();
  server.on("/", HTTP_GET, handleRoot); //used to call the handleroot function when client requests a url  
  server.on("/BUZ", HTTP_POST, handleBUZ);  //access the webpage created;calls the handleBUZ function when a post request is made to the url
  server.onNotFound(handleNotFound);        
  server.begin();                           
  Serial.println("HTTP server started\n");
}
void loop(void){ //read buzzer state from webpage and change the pin state to turn buzzer on/off
  server.handleClient();                    
  if (buzzing_state == true) {
    digitalWrite(buz_pin, HIGH);//buzzer to alert
      delay(400);
        yield();
    digitalWrite(buz_pin, LOW);//buzzer to remain off
     delay(200);
      yield();
       delay(400);
        yield();
  }
}
