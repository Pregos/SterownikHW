//Obsługa Wifi za pomocą arduino uno i esp8266

//Serial - usunąć do produkcji
//SoftwareSerial - usunąć do  produkcji


#include <SoftwareSerial.h>


//String wifiSID = "pregosie24";
//String wifiPass = "*******************";

//The circuit:
// * RX is digital pin 10 (connect to TX of other device)
// * TX is digital pin 11 (connect to RX of other device)

SoftwareSerial esp(10, 11); // RX, TX

void setup() {
  // open hardware serial monitor
  Serial.begin(9600);
  //waiting for open serial monitor
  while(!Serial);


  //open software serial to esp8266
  esp.begin(115200);

  //waiting for ESP8266
  while (!wyslij("AT","OK",200))
  {
    Serial.println("ESP8266: Communication error!");
    delay(250);
  }
  Serial.println("ESP8266: Communication started");



  //sets wifi mode to station mode (no access point)
  if (sendCommand("AT+CWMODE?", 5, "+CWMODE:1", 250))
  {
    Serial.println("CWMODE - OK!");
  }
  else
    if (sendCommand("AT+CWMODE=1", 5, "OK", 250))
    {
      Serial.println("CWMODE - Set!");
    }
    
  //set transfer mode to normal 
  if (sendCommand("AT+CIPMODE?", 5, "+CIPMODE:0", 250))
  {
    Serial.println("CIPMODE - OK!");
  }
  else
    if (sendCommand("AT+CIPMODE=0", 5, "OK", 250))
    {
      Serial.println("CIPMODE - Set!");
    }
  
  //enable multiply connections
  if(sendCommand("AT+CIPMUX?", 5, "+CIPMUX:1", 250))
  {
    Serial.println("CIPMUX - OK!");
  }
  else
    if(sendCommand("AT+CIPMUX=1", 5, "OK", 250))
    {
      Serial.println("CIPMUX - Set!");
    }
  
  //enable dhcp for client  
  if(sendCommand("AT+CWDHCP=1,1", 5, "OK", 500))
  {
    Serial.println("CWDHCP - Set!");
  }

  
  //wifi login
  if (sendCommand("AT+CWJAP?", 5, "Pregosie24", 2000))
  {
    Serial.println("WiFi already connected!");
  }
  else
    if (sendCommand("AT+CWJAP=\"pregosie24\",\"**********************\"", 5, "OK", 2000))
    {
      Serial.println("WiFi connected!");
    }

  //run WWW server
  if(sendCommand("AT+CIPSERVER=1,80", 5, "OK", 500))
  {
    Serial.println("Server WWW started");
  }

  esp.println("AT+CIFSR");
  delay(2000);

  esp.println("AT+CIPSTA?");
  delay(2000);
  Serial.println(esp.readString());
  
}


//main loop
void loop() {
  //Serial.println("bla");

  if(wyslij("AT","OK",200))
  {
    //Serial.println("ESP8266 ok");
  }

  delay(2000);
  
}


boolean wyslij(String Komenda_AT, char *Odpowiedz_AT, int czas_czekania)
{
  esp.println(Komenda_AT);
  delay(czas_czekania);
  while(esp.available()>0)
  {
    if(esp.find(Odpowiedz_AT))
    {
      return 1;
    } 
  }
  return 0;
}


bool sendCommand(String command, int maxTime, char readReplay[], int waitTime) 
{
  int countTimeCommand = 0;
  int countTrueCommand = 0;
  boolean found = false;
  
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp.println(command);//at+cipsend
    delay(waitTime);
    if(esp.find(readReplay))//ok
    {
      Serial.println(readReplay);
      found = true;
      break;
    }
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  Serial.println("KONIEC");
  return found;
}
