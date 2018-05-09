#include <ArduinoOSC.h>

WiFiUDP udp;
ArduinoOSCWiFi osc;
const char* ssid = "Don't worry, be happy!";
const char* pwd = "whyistheskysohigh?";
//const char* ssid = "TPH Operations";
//const char* pwd = "TheFUTURE!Sno3";
const IPAddress ip(192, 168, 178, 201);
const IPAddress gateway(192, 168, 178, 1);
const IPAddress subnet(255, 255, 255, 0);
const char* host = "192.168.178.20";
//const char* host = "192.168.20.65";
const int recv_port = 10000;
const int send_port = 9000;

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = 32;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot

OSCMessage oscMessage;

void setup()
{
    Serial.begin(115200);
    WiFi.disconnect(true);
    WiFi.onEvent(onWiFiEvent);
    WiFi.begin(ssid, pwd);
    //WiFi.config(ip, gateway, subnet);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    osc.begin(udp, recv_port);
    osc.addCallback("/ard/aaa", &callback);
    osc.addCallback("/ard", &callback);
}

void loop()
{
    osc.parse();

    sensorValue = analogRead(analogInPin);
    oscMessage.beginMessage(host, send_port);
    
   
    oscMessage.setOSCAddress("/amazon/arduino/baldosa1");
    oscMessage.addArgInt32(sensorValue);
    osc.send(oscMessage);

    Serial.print("sensor = ");
    Serial.println(sensorValue);

    oscMessage.beginMessage(host, send_port);
    oscMessage.setOSCAddress("/amazon/arduino/sentrada");
    
   
    if(sensorValue>15){
      oscMessage.addArgInt32(1);
       Serial.print("pir = 1");
    }
    else{
       oscMessage.addArgInt32(0);
       Serial.print("pir = 0");
    }

    osc.send(oscMessage);
    
    delay(2);
    
}

void callback(OSCMessage& m)
{
    //create new osc message
    OSCMessage msg;
    //set destination ip address & port no
    msg.beginMessage(host, send_port);
    //set argument
    msg.setOSCAddress(m.getOSCAddress());
    msg.addArgInt32(m.getArgAsInt32(0));
    msg.addArgFloat(m.getArgAsFloat(1));
    msg.addArgString(m.getArgAsString(2));
    //send osc message
    osc.send(msg);
}

void onWiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
        case SYSTEM_EVENT_STA_START:
        {
            Serial.println("STA Started");
            break;
        }
        case SYSTEM_EVENT_STA_CONNECTED:
        {
            Serial.println("STA Connected");
            break;
        }
        case SYSTEM_EVENT_STA_GOT_IP:
        {
            Serial.print("STA IPv4: ");
            Serial.println(WiFi.localIP());
            break;
        }
        case SYSTEM_EVENT_STA_DISCONNECTED:
        {
            Serial.println("STA Lost Connection");
            break;
        }
        case SYSTEM_EVENT_STA_STOP:
        {
            Serial.println("STA Stopped");
            break;
        }
        default:
        {
            break;
        }
    }
}
