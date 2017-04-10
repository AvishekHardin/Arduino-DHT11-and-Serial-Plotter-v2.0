#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define switchPin 3

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean tempORhum = LOW;    //temp = LOW, Hum = HIGH to be displayed on the Serial Plotter

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(t) || isnan(h)){
    return;
  }
  
  currentButton = debounce(lastButton);       
  if(lastButton == LOW && currentButton == HIGH){   
    tempORhum = !tempORhum;
  }
  lastButton = currentButton;
  
  if(tempORhum == LOW){
    Serial.println(t);
  }else{
    Serial.println(h);
  }
  delay(500);
}

boolean debounce(boolean last){
  boolean current = digitalRead(switchPin);
  if(last != current){
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}
