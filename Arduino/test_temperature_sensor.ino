int led = 13; // define the LED pin
int digitalPin = 2; // KY-028 digital interface
int analogPin = A0; // KY-028 analog interface
int digitalVal; // digital readings
int analogVal; //analog readings
float Analog;
float analog_Val;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  //pinMode(analogPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPin); 
  if(digitalVal == HIGH) // if temperature threshold reached
  {
    digitalWrite(led, HIGH); // turn ON Arduino's LED
  }
  else
  {
    digitalWrite(led, LOW); // turn OFF Arduino's LED
  }
  // Read the analog interface
  analogVal = analogRead(analogPin)*(5.0/1023.0); 
  Analog = analogVal*0.4882815;

  
  Serial.println("Temperatura Medida :");
  Serial.println(Analog); // print analog value to serial
  delay(100);

}
