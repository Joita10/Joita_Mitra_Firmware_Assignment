
/* Here in this sketch we will be interfacing Temperature Sensor LM35 and we need to blink onboard led
If the temperature falls below 30 degree C it blink rapidly or after every 250 ms
If the temperature rises above 30 degree C it blink slightly slower or after every 500 ms

millis(), micros(), delay() are not used*/


#include <LiquidCrystal.h>
#include<millisDelay.h>

#define temp A0
int led = 13;
bool ledOn = false;
float pre_temp = 0; //This variable tests if the temperature is changing or not

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


millisDelay ledDelay; //Defining Class with a name-tag "ledDelay" to produce repeated Delay


//Creating a Function for producing delay

void produce_delay(unsigned int delay_time){
  
  ledDelay.start(delay_time);
  //infinite loop

  while(1){

    if(ledDelay.justFinished()){

      ledDelay.repeat();
      ledOn = !ledOn;
      if(ledOn){
        digitalWrite(led,HIGH);
      }
      else{
        digitalWrite(led,LOW);
      }

    }
  }
}
  

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(temp, INPUT);
  Serial.begin(9600);
  lcd.clear();
  lcd.print("Temperature: ");
}

void loop() {

  float temperature = 0;
  temperature = ((analogRead(temp) * (5.0/1023)) - .4995)*100; //where .4995V or approx .5V is the offset voltage
  
  if(pre_temp != temperature)
  {
    lcd.setCursor(0,1);
    lcd.print("                ");
  }
  
  if(temperature<30){
    produce_delay(250); 
    //producing delay without delay(),millis(),micros()
  }
  
  else if(temperature>=30){
    produce_delay(500); 
    //producing delay without delay(),millis(),micros()
  }
  
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print(" C");
  pre_temp = temperature;
  
}