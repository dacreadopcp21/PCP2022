// Arduino - Nivel de Agua e Ingreso.

#include <Servo.h>  // Libreria Servo Motor para Bomba
#include <Keypad.h>

// Configuración del KeyPad
byte rows = 4; 
byte cols = 4; // Setup 4*4 keypad 
char keys[4][4] = { // 2D Array Claves (OP)
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[4] = {9, 8, 7, 6}; // Pins para mapear filas
byte colPins[4] = {5, 4, 3, 2}; // Pins para mapear columnas


Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols); // Interfaz Byte


Servo svr;

// Auxiliares
char gas = A0; 
int echo = 10; 
int trig = 11; 
int serv = 12; // Control Angulo ServoMotor
int buzz = 13; 

// Declaraciones Estaticas

String password= "0000"; // Contiene Clave Maestra 0000 
String pressed=""; // Contiene Clave Ingresada

float distance; // Sensor Ultrasonido 
float gaser; 

int flag = 0; // trigger Autenticación

// Delaración de Funciones (Measure == Medida)
float measureDistance(int, int); 
float measureSmoke(int); 
void checkKeyPad(); 
void setup() {
    Serial.begin(1156200); // Serial Monitor para Com.  pinMode(trig, OUTPUT); // Envío Señal Trigger
    Serial.flush();  
  
    pinMode(trig, OUTPUT); 
    pinMode(echo, INPUT); 
    pinMode(gas, INPUT); 
    pinMode(buzz, OUTPUT); 

    svr.attach(serv); 
}

void loop()
{
    distance = 0.01723 * measureDistance(trig, echo); // 340 * 100 * 0.00001 / 2
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println();
    if (distance > 200) { // Lectura al nivel de agua / profundidad
      for (int i = 0; i <= 180; i++) {
          svr.write(i);
            delay(5); 
        }
      delay(50);
        for (int i = 180; i >= 0; i--) {
            svr.write(i); 
            delay(5);
        }
    } else {
        svr.write(0); 
    }

    gaser = measureSmoke(gas); // Lectura de Gas
    Serial.print("Gas: ");
    Serial.print(gaser);
    Serial.println();
    if (gaser > 100) {
        for (int i = 200; i <= 600; i += 50) {
            tone(buzz, i, 10); // Tocar buzzing
            delay(5);
        }
    } else {
        digitalWrite(buzz, 0); // Parar buzz
    }
    svr.write(0);
    delay(20);
}

// Distancia
float measureDistance(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Trigger 10 microsegundos
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    return pulseIn(echoPin, HIGH);
}

// Mide la cantidad de humo en el ambiente.
float measureSmoke(int pin) {
    return analogRead(pin);
}

// Eventos - Matriz
void checkKeyPad() {
    char key = kp.getKey();
    if (int(key) != 0) {
        if (key == 'C') { // Borrar ingreso por teclado
          pressed = "";
            delay(100); // Limpiar cache
        } else if (key == '*') { // Ingreso check de pass
          if (pressed == password) {
                flag = 1; // salida del loop de verificación
            }
          Serial.write(char('w'));
        } else {
          pressed.concat(key);  
            Serial.write(char(key));
        }
    }
}
