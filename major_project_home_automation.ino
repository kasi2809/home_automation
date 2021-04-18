#include <SoftwareSerial.h>
#define relay 8//Initializing relay pin
String Wifi_name="OPPO A5S";
String Password="Ka$i2002";
String getdata,data_recd="";
int light_status=0;
char r;
SoftwareSerial esp(3,2);
void setup() {
  esp.begin(9600);
  pinMode(relay,OUTPUT);
  esp.println("AT+RST");
  esp.println("AT+CWMODE=1");
  esp.println("AT+CWJAP=\""+Wifi_name+"\",\""+Password+"\"");
  while(!esp.find("OK"))
  {
//Wait for connection
  }
  Serial.println("Connection Successful");
  
  
}

void loop() {
  getdata="GET /channels/1094231/fields/1.json?api_key=G5RS7J0GJHXQJ94G&results=1";
  esp.println("AT+CIPMUX=0");
  esp.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80"); 
  esp.println("AT+CIPSEND="+String(getdata.length()));
  esp.find(">");
  esp.println(getdata);
  while(esp.available()==0)
  {   
  }
  while(esp.available()!=0)
  {r=esp.read();
  data_recd=data_recd+r;}

  light_status=int(data_recd[data_recd.length()-5]);
  if(light_status==1)
  {digitalWrite(relay,HIGH);
  Serial.println("LIGHTS ON");}
  else
  {digitalWrite(relay,LOW);
  Serial.println("LIGHTS OFF");}
  data_recd="";
  esp.println("AT+CIPCLOSE=0");
  delay(500);
}
