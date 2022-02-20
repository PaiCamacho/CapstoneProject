int led = 13; // the pin that the LED is attached to
int sensor = 2;// the pin that the sensor is attached to
int val = 0;
bool isON = false;

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial
}
void loop(){
  val = digitalRead(sensor);
  if(val == HIGH){
    isON = true;
    digitalWrite(led, HIGH);
  }
  while(isON){
    val = digitalRead(sensor);
    if(val == HIGH){
      isON = false;
      digitalWrite(led, LOW);
    }
  }
}
