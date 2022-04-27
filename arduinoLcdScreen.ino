// include the library code:
#include <LiquidCrystal.h>
#include <dht.h>
#define dht_apin A0
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 7;
int servoPin2 = 10; 
// Create a servo object 
Servo Servo1;
Servo Servo2; 
int sensor = 6;
int val = 0;
bool isON = false;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht DHT;
char line0[21]; 
char line1[21];

//04 / 29 / 2022
//Enter Today's current numerical month
int month = 4;
//Enter Today's current numerical day
int day = 29;
//Enter Today's current numerical year
int year = 2022;
  

//03 : 30 PM  
//Enter Today's current numerical hour
int hour = 3;
//Enter Today's current numerical minute
int minute = 30;
//Enter PM or AM
String m = "PM";


unsigned long lastTimerTime = millis();

int tick = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  line0[4] = 8; 
  line0[5] = 5; 
  Servo1.attach(servoPin); 
  Servo2.attach(servoPin2); 
  pinMode(sensor, INPUT);    
  Serial.begin(9600); 
  Servo1.write(180);
  Servo2.write(0);
}

void updateDisplay() {
  lcd.setCursor(0,0);
  lcd.print(line0);
  lcd.print(line1);
}

//OUTPUT: Temperature: 00F
void temperatureDisplay(){
  DHT.read11(dht_apin);
  int temperatureRead = DHT.temperature;
  temperatureRead = (((9/5)*temperatureRead)+32);
  
  lcd.print("Temperature: ");
  lcd.print(temperatureRead);
  lcd.print("F");
  updateDisplay(); // update display reading each loop
}
//OUTPUT: Humidity: 00%
void humidityDisplay(){
  DHT.read11(dht_apin);
  int humidityRead = DHT.humidity;

  lcd.print("Humidity: ");
  lcd.print(humidityRead);
  lcd.print("%");
  lcd.print("   ");
  updateDisplay(); // update display reading each loop
}

// OUTPUT: 00 / 00 / 0000
void dateDisplay(){
  if(month < 10){
    lcd.print("0");
  }
  lcd.print(month);
  lcd.print(" / ");
  
  if(day < 10){
  lcd.print("0");
  }
  lcd.print(day);
  lcd.print(" / ");
  lcd.print(year);
  lcd.print("  ");
  updateDisplay();
}

//OUTPUT: 00 : 00 0M
void timeDisplay(){
  if(hour < 10){
    lcd.print("0"); 
  }
  lcd.print(hour);
  lcd.print(" : ");
  
  if(minute < 10){
    lcd.print("0");
  }
  lcd.print(minute);
  lcd.print(" ");
  lcd.print(m);
  lcd.print("      ");
  
  if(millis() - lastTimerTime > 60000){
    minute += 1;
    lastTimerTime = millis();
    if(minute == 60){
      hour += 1;
      minute = 0;
      if(hour == 12){
        if(m == "PM"){
          m = "AM";
        }
        else if(m == "AM"){
          m = "PM";
        }
      }
      else if(hour == 13){
        hour = 1;  
      }
    }
  }
  updateDisplay();
}

void loop() {
  val = digitalRead(sensor);
  if(val == HIGH && isON != true){
    isON = true;
    Servo1.write(0);
    Servo2.write(180);
    delay(2000);
  }
  else if(val == HIGH && isON == true){
    Servo1.write(180);
    Servo2.write(0);
    isON = false;
    delay(2000);
  }
    tick += 1;
    int task = tick / 200 % 4;
    switch (task) {
      case 0:
        temperatureDisplay();
        break;
      case 1:
        humidityDisplay();
        break;
      case 2:
        dateDisplay();
        break;
      case 3:
        timeDisplay();
        break;
    }
}
