#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int gassen=A1;
int valuesen;
int firesen=A0;
int valuesen1;

const int  in_1 = 6 ;
const int  in_2 = 7 ;
int Water=8;
int buzz=9;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(gassen,INPUT);
delay(2000);
pinMode(in_1,OUTPUT) ;  
pinMode(in_2,OUTPUT) ;
pinMode(Water,OUTPUT) ;
pinMode(buzz,OUTPUT);

}

void loop() {
 
  // put your main code here, to run repeatedly:
GAS();
FIRE();

}

void GAS()
{
  valuesen=analogRead(gassen);
Serial.println(valuesen);
delay(1000);
if(valuesen>450)
{
  Serial.println("smoke detected");
  lcd.clear();
  lcd.print("smoke detected");
  delay(2000);
digitalWrite(buzz,HIGH) ;
delay(1500);
digitalWrite(buzz,LOW) ;
delay(1500);
}
else
{
  Serial.println("smoke not detected");
}
}
}

void FIRE()
{
  valuesen=analogRead(firesen);
Serial.println(valuesen1);
delay(1000);
if(valuesen1>450)
{
  Serial.println("fire detected");
  lcd.clear();
  lcd.print("fire detected");
  delay(2000);
  digitalWrite(buzz,HIGH) ;
delay(1500);
digitalWrite(buzz,LOW) ;
delay(1500);
  digitalWrite(Water,HIGH) ;
delay(1500);
digitalWrite(Water,LOW) ;
delay(1500);


}
else
{
  Serial.println("fire detected");
}
}
}
