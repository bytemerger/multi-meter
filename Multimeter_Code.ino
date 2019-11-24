

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_INA219.h> // You will need to download this library
LiquidCrystal lcd(3,4,5,6,7,8);

Adafruit_INA219 sensor219; // Declare and instance of INA219


 
const int buzzerPin = A3;

//Ohmmeter Analog Pin
int vin = A2;

//Autoranging Ohmmeter variables
int t=12;
int u=11;
int v=10;
int w=9;


int at;
int au;
int av;
int aw;

int a;
double vx;
float rx;
double i;

//Push Button
int state =0;
boolean button;
boolean lastButton = LOW;

int continuity;




void setup() 
{
  //code for the buzzer song
  pinMode(buzzerPin,OUTPUT);
  pinMode(vin,INPUT);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("Select");
  lcd.setCursor(0,1);
  lcd.print("1:Volt 2:Continuity");
  lcd.setCursor(0,2);
  lcd.print("3:Current 4:Ohms");
  lcd.print((char)244);
    
  sensor219.begin();
  pinMode(13, INPUT);
  

  pinMode(t,OUTPUT);
  pinMode(u,OUTPUT);
  pinMode(v,OUTPUT);
  pinMode(w,OUTPUT);
  
  digitalWrite(t,LOW);
  digitalWrite(u,LOW);
  digitalWrite(v,LOW);
  digitalWrite(w,LOW);
  
  
}

void loop(void) 
{
  
  button= debounce(lastButton);
  
  if(button==HIGH){
    state = state + 1;
    if(state >= 5)state=1;
    }
  
  
 

  
  float busVoltage = 0;
  float current = 0; // Measure in milli amps

  busVoltage = sensor219.getBusVoltage_V();
  current = sensor219.getCurrent_mA();
  
  switch (state){
    case 1:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Bus Voltage:   "); 
       lcd.setCursor(0,1);
       lcd.print(busVoltage); 
       lcd.print(" V"); 
       lcd.setCursor(0,3);
       lcd.print(state);
  delay(1000);
     break;
    case 2:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Continuity:"); 
       continuity= digitalRead(2);
       if(continuity==LOW){
        
        digitalWrite(buzzerPin, HIGH);
        lcd.print("1");
        delay(1000);
        }
        else{
          
          digitalWrite(buzzerPin, LOW);
          lcd.print("0");
          }
          lcd.setCursor(0,3);
          lcd.print(state);
          delay(1000);
     break;
    case 3:
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Current:"); 
       lcd.setCursor(0,1);
       lcd.print(current); 
       lcd.print(" mA");
       lcd.setCursor(0,3);
       lcd.print(state);
  delay(1000);
     break;
    case 4:
        //lcd.clear();
        digitalWrite(t,HIGH);
        digitalWrite(u,LOW);
        digitalWrite(v,LOW);
        digitalWrite(w,LOW);
        delay(100);
        
        at=analogRead(vin);
        
        
        
        digitalWrite(t,LOW);
        digitalWrite(u,HIGH);
        digitalWrite(v,LOW);
        digitalWrite(w,LOW);
        
        delay(100);
        
        au=analogRead(vin);
        digitalWrite(t,LOW);
        digitalWrite(u,LOW);
        digitalWrite(v,HIGH);
        digitalWrite(w,LOW);
        
        delay(100);
        av=analogRead(vin);
        
        
        
        digitalWrite(t,LOW);
        digitalWrite(u,LOW);
        digitalWrite(v,LOW);
        digitalWrite(w,HIGH);
        
        delay(100);
        aw=analogRead(vin);
        
        
        
        lcd.clear();
        if(aw>=450)
        {
        vx=aw*0.00489;
        i=(5-vx-0.58)/1040200;
        rx=(vx/i);
        }

        if(at>=430 && aw<430)
        {
        vx=at*0.00489;
        i=(5-vx-0.57)/101100;
        rx=(vx/i);
        
        }

        if(au>=430 && at<430 && aw<430)
        {
        vx=au*0.00489;
        i=(5-vx-0.55)/940;
        rx=(vx/i);
        }
        
        if(av>=439 && aw<430 && au<430 && at<430)
        {
        vx=av*0.00489;
        i=(5-vx-0.55)/210;
        rx=(vx/i);
        }
        
        
        
        
        lcd.setCursor(0,0);
        
        if(vx>4.8)
        {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("----INFINITY----");
        //delay(1000);
        }
        else
        {
        if(rx<1000)
        {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(rx);
        lcd.setCursor(7,0);
        lcd.print((char)244);
        
        }
        else
        {
        lcd.clear();
        rx=rx/1000;
        lcd.setCursor(0,0);
        lcd.print(rx);
        lcd.setCursor(6,0);
        lcd.print("k");
        lcd.print((char)244);
        
        }
        }
        lcd.setCursor(0,1);
        lcd.print("Arduino Ohmmeter");
        lcd.setCursor(0,3);
        lcd.print(state);
    delay(1000);
     break;
     
  }
  lastButton = LOW;
 
}

  boolean debounce(boolean last){
  button = digitalRead(13);
  if(last != button){
    delay(20);
    button = digitalRead(13);
  }
  return button;
}
