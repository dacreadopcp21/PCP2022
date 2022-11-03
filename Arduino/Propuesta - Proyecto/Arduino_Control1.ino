// Monitoreo Invernadero
#include <LiquidCrystal.h>  

// Conexión Pantalla LCD
int regSel = 7;  
int enable = 6; 
int sig1 = 5; 
int sig2 = 4; 
int sig3 = 3; 
int sig4 = 2; 

// Enfriador y Calefactor
int motor1 = 8; 
int motor2 = 9; 
int motor3 = 10; 
int motor4 = 11; 

// Control de luz artificial
int light = 12; // led 

// Sensores
char temp = A0; // Sensor Temperatura
char lumos = A1; // Fotoresistor

// Variables Auxiliares
float temperature; 
float intensity; 
int flag = 0; 

// Inicialización en LCD
LiquidCrystal lcd(regSel, enable, sig1, sig2, sig3, sig4);

// Declaración de Funciones
float readTemperature(char); // Temperatura
float readLuminousity(char); // Intensidad de Luz
void authenticate(); 

void setup() {
    // Pins  
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(motor3, OUTPUT);
    pinMode(motor4, OUTPUT);
    pinMode(light, OUTPUT);

    // Pins Lectura
    pinMode(temp, INPUT);
    pinMode(lumos, INPUT);

    // Serial monitor 
    Serial.begin(1156200); // baud rate de 1156200 OJO No 9600
    // LCD 
    Serial.flush();
    lcd.begin(16, 2); // 16*2 Dimensiones de LCD
}

void loop() {
    lcd.clear();
  temperature = readTemperature(temp); 
    lcd.setCursor(3, 0); // Posición LCD
    lcd.print("Temp: "); 
    lcd.setCursor(9, 0); 
    lcd.print(temperature);
    if (temperature < 20) { 
      lcd.setCursor(4, 1);
      lcd.print("BAJA TEMPERATURA"); 
        digitalWrite(8, HIGH); // Habilita calefactor
        digitalWrite(10, LOW); // No enfriador
    } else if (temperature > 27) { // Temperatura de Control
        lcd.setCursor(4, 1); 
      lcd.print("ALTA TEMPERATURA");
        digitalWrite(8, LOW); // No calefactor
        digitalWrite(10, HIGH); // Habilita enfriador
    } else {
        lcd.setCursor(4, 1); 
      lcd.print("TEMPERATURA REGULAR");
        digitalWrite(8, LOW); 
        digitalWrite(10, LOW);
    }
    digitalWrite(9, LOW); // Previene movimiento anticlockwise 
    digitalWrite(11, LOW);
    delay(150);
    lcd.clear();
    intensity = readLuminousity(lumos); // Lectura luz
    lcd.setCursor(1, 0);
    lcd.print("Intensidad: "); 
    lcd.setCursor(12, 0);
    lcd.print(intensity); 
    if (intensity < 100) { // Oscuro / Noche
      lcd.setCursor(4, 1);
      lcd.print("MUY OSCURO");
        digitalWrite(light, HIGH); 
    } else  if (intensity > 180) { // Mañana
        lcd.setCursor(4, 1);
      lcd.print("MUY CLARO");
    } else {
        lcd.setCursor(4, 1);
      lcd.print("PERFECTO");
    }
    delay(150);
    digitalWrite(light, LOW); 
}

// Lectura de temperatura y conversión a Celsius
float readTemperature(char pin) {
    float volts = analogRead(pin); // Codificación milivolts 8BCD enncoding
    float value = map(((volts - 20) * 3.04), 0, 1023, -40, 125); // Rango de  -40C a 125C
    return value;
}

// Lectura de luz y conversión a luminosidad
float readLuminousity(char pin) {
    float lum = analogRead(pin); //  ( Blanco - Negro) 0 - 1023
    float value = map(lum, 0, 700, 0, 255); //Rango de lectura intensidad de luz
    return value;
}


// Función Auxiliar 
void authenticate() {
  lcd.setCursor(1,0);
  if (char(Serial.read()) == 'w')
  lcd.print('y');
  else
  lcd.print('n');
  
}
