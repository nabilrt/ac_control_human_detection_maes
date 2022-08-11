#include <LiquidCrystal.h>
#include <dht.h>


#define dht_apin  A1
dht DHT;

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

int sensor = 7;              
int state = LOW;             
int val = 0;  

int in1 = 11; 
int in2 = 10;
int ConA = 9;
int speed1;



void setup() {
 
 lcd.begin(16, 2);
 pinMode(sensor, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
 
}

void loop() {
  val = digitalRead(sensor); 
 
  if (val == HIGH){
    DHT.read11(dht_apin);
    float tempC = DHT.temperature;
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Motion detected!");
if(tempC < 18.00){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,0);
     
    
   
      lcd.setCursor(0,1);
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 
             
      lcd.print(" S: 0"); 
     
    }
    
    else  if(tempC >= 18.00 && tempC < 24.00){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,100);

 
      lcd.setCursor(0,1);  
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 

      lcd.print(" S: 100"); 
     
    }
    
    else  if(tempC >= 24.00 && tempC < 28.00){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,200);

      lcd.setCursor(0,1);  
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 
            

      lcd.print(" S: 200"); 
    }


    else  if(tempC >= 28){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,255);
         

      lcd.setCursor(0,1);  
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 
              
      lcd.print(" S: 255"); 
    }

    delay(10000);
    
    if (state == LOW) {
      state = HIGH;       
    }
    
    }
       
  else { 
    lcd.clear();
    lcd.print("Motion stopped!");
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,0);
    delay(100);
    
      if (state == HIGH){;
        state = LOW;       
    }
  }
    

}
