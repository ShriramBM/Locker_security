
#include "CTBot.h"        //arduino json should be 5.13.2v
#define  msg_sender_id 768800058



CTBot myBot;
String ssid = "android";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "99008849999";
 // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1903078604:AAFA6hnwnKtGcsBN1_L5Jb-RAAHUBR3LljA"; 

uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin    // con
                            // (replace 2 with BUILTIN_LED)    
char Start_buff[70]; 
int i,z;             
char ch;
int str_len;
 char textmessage[20];
TBMessage msg;
void MESSAGE_SEND();
void WAITING();
void setup() 
{
    // initialize the Serial
    Serial.begin(9600);
    Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
    myBot.setTelegramToken(token);
   // myBot.setTelegramToken(token1);

    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");
  
   TEST();
    //MESSAGE_SEND();
}
void loop() 
{
  
  
  WAITING();
  
  //MESSAGE_RECEIVE();
      
}
void MESSAGE_SEND()
{
   myBot.sendMessage(msg_sender_id, "SEND START TO CONTINUE"); 
  // myBot.sendMessage(msg_sender_id1, "WELCOME TO ERATION"); 
  
}
void MESSAGE_RECEIVE()
{
    msg.text[0]='\0';
        msg.text[1]='\0';
         msg.text[2]='\0' ;
         msg.text[3]='\0';
          msg.text[4]='\0';
           msg.text[5]='\0';
           buffer1_clear();
   while(1)
   {
     if (myBot.getNewMessage(msg))
     { 
    
      String message = msg.text;
      String str = "C";
      String all = str + message;
      // Convert String to char array
      int str_len = message.length() + 1;
      char textmessage[str_len];
      message.toCharArray(textmessage,str_len);
          //delay(1000);                         
    //Serial.println(textmessage);
    
       if((textmessage[0]=='*')&&(textmessage[3]=='#')||((textmessage[4]=='#')||(textmessage[5]=='#')))
       {        
          // Serial.println("VALID");
            Serial.println(textmessage); 
           buffer1_clear();
//            buffer_clear();
            WAITING();
       }
        else
        {                                                    // otherwise...
            // generate the message for the sender
            String reply;
            reply = (String)"YOU HAVE ENTER WRONG FORMAT " + msg.sender.username + (String)". Try PROPER FORMAT";
            myBot.sendMessage(msg.sender.id, reply);             // and send it
            
        }
    }
  
    delay(500);
    
   
   }
  
}

char Serial_read(void)
{
      char ch;
      while(Serial.available() == 0);
      ch = Serial.read(); 
      return ch;
}
void WAITING()
{
   Serial.println("WAITE");
  
  buffer_clear();

           
 while(1)
 { 
      if (Serial.available() > 0)
      {
        
          while(Serial_read()!='$');
          i=0;
          while((ch=Serial_read())!='#')
          {
            Start_buff[i] = ch;
             i++;
          }  
          Start_buff[i]='\0';
       }
     Serial.println(Start_buff);
     
     myBot.sendMessage(msg_sender_id, Start_buff); 
    delay(1000);


if(strcmp(Start_buff,"EMERGENCY...")==0)
     {
      // Serial.println("HI");
      
      //buffer_clear();
     String one = "EMERGENCY AT:https://www.google.com/maps/?q=";
                      //  String two = ',' ;   
            String message = one +"12.5547" +','+ "77.3720"+"";
            String all = message;
                      // Convert String to char array
            int str_len = message.length() + 1;
            char textmessage[str_len];
            message.toCharArray(textmessage,str_len);
                      // 
     
        Serial.write(textmessage);
      Serial.write("\n\r\r");
      
       myBot.sendMessage(msg_sender_id, textmessage); 
     }
    
 }

 }


void buffer_clear()
{
  for(z=0;z<60;z++)
  {
    Start_buff[z]='\0';
//    textmessage[z]='\0';
    
  } 
}
void buffer1_clear()
{
  for(z=0;z<5;z++)
  {
   
   textmessage[z]='\0';
    
  } 

}
void TEST()
{

String ssid = "android";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "99008849999";
 // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1903078604:AAFA6hnwnKtGcsBN1_L5Jb-RAAHUBR3LljA"; 
//String token1 = "922509739:AAEuwh7DqyVprK55jlyGhVJ0RHWSSVeQTYg"; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)                            

 TBMessage msg;


    // initialize the Serial
    Serial.begin(9600);
    Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
    myBot.setTelegramToken(token);

    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");

    // set the pin connected to the LED to act as output pin
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH); // turn off the led (inverted logic!)
   //myBot.sendMessage(msg_sender_id, "WELCOME TO E-RATION DISTRIBUTION SYSTEM"); 
MESSAGE_SEND();
  
while(1) {
    // a variable to store telegram message data

    // if there is an incoming message...
    if (myBot.getNewMessage(msg)) {

        if (msg.text.equalsIgnoreCase("START")) {              // if the received message is "LIGHT ON"...
            digitalWrite(led, HIGH);                               // turn on the LED (inverted logic!)
            myBot.sendMessage(msg.sender.id, "WELCOME TO  BANK SECURITY SYSTEM");  // notify the sender
         Serial.println(msg.sender.id);
          WAITING();
        }
         else {                                                    // otherwise...
            // generate the message for the sender
            String reply;
            reply = (String)"Welcome " + msg.sender.username + (String)". Try START";
            myBot.sendMessage(msg.sender.id, reply);             // and send it
            
        }
    }
    // wait 500 milliseconds
    delay(500);
}
 
  
}
