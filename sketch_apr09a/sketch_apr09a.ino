#include <dht.h>


#define dht_apin  A1 // Analog Pin sensor is connected to

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 6, 5, 4, 3);


dht DHT;

int distanceThreshold = 0;
int cm = 0;
int inches = 0;

int in1 = 10; //Declaring where our module is wired
int in2 = 11;
int ConA = 9;// Don't forget this is a PWM DI/DO
int speed1;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
 pinMode(triggerPin, OUTPUT); // Clear the trigger
 digitalWrite(triggerPin, LOW);
 delayMicroseconds(2);
 // Sets the trigger pin to HIGH state for 10 microseconds
 digitalWrite(triggerPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin, LOW);
 pinMode(echoPin, INPUT);
 // Reads the echo pin, and returns the sound wave travel time in microseconds
 return pulseIn(echoPin, HIGH);
}




void setup() {
  Serial.begin(9600);        // initialize serial
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);

}

void loop(){
   // set threshold distance to activate LEDs
  distanceThreshold = 30;
// measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(8, 7);
  // convert to inches by dividing by 2.54
inches = (cm / 2.54);
// convert to inches by dividing by 2.54
 inches = (cm / 2.54);
 Serial.print(cm);
 Serial.print("cm, ");
 Serial.print(inches);
 Serial.println("in");
Serial.println();


 if (cm <= distanceThreshold ){          // check if the sensor is HIGH

    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(5000);
    Serial.println("Motion detected!"); 
    lcd.clear();
    lcd.print("Motion detected!");
    float tempC = DHT.temperature;

     if(tempC < 18.00){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,0);
     
      Serial.print("T= "); 
      Serial.print(tempC,1);
      Serial.println(" C");
       Serial.println(" speed: 0");
    
   
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

      Serial.print("T= "); 
      Serial.print(tempC,1);
      Serial.print(" C");
 
      lcd.setCursor(0,1);  
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 
      Serial.println(" speed: 100");

      lcd.print(" S: 100"); 
     
    }
    
    else  if(tempC >= 24.00 && tempC < 28.00){
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,200);


      Serial.print("T= "); 
      Serial.print(tempC,1);
      Serial.print(" C");
      Serial.println(" speed: 200");
 
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

      Serial.print("T= "); 
      Serial.print(tempC,1);
      Serial.print(" C");
      Serial.println(" speed: 255");
         

      lcd.setCursor(0,1);  
      lcd.print("T: ");
      lcd.print(tempC);
      lcd.print("C"); 
              
      lcd.print(" S: 255"); 
    }

    delay(30000);
    
  } 
  else {

     DHT.read11(dht_apin);
    
        
    digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
    digitalWrite(in2, HIGH);
    analogWrite(ConA,0);
    
    lcd.clear();
    lcd.print("Motion stopped!");
    Serial.println("Motion stopped!");
    delay(5000);  
  }
}
