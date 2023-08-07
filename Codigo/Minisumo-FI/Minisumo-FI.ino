// Minisumo-FI
// Este código es para el uso de Arduino Nano y el driver TB6612FNG
// Este código es específico para un sensor ultrasónico
//Autor: Eduardo Rivera



// Definición de pines
int ultrasonicDuration;
int distanceCm;
int ticCounter;
int robotState = 0;

// Variables del ultrasonido
int trigPin = 6;  // Pin de trigger del sensor ultrasónico
int echoPin = 7;  // Pin de eco del sensor ultrasónico

// Velocidad de los motores
int motorSpeed = 200;  // Puedes cambiar este valor según sea necesario

// Pines del motor
int pinAIN1 = 2;   // Control de dirección motor 1
int pinAIN2 = 3;   // Control de dirección motor 1
int pinBIN1 = 4;   // Control de dirección motor 2
int pinBIN2 = 8;   // Control de dirección motor 2
int pinPWMA = 9;   // Control de velocidad motor 1
int pinPWMB = 10;  // Control de velocidad motor 2

// Funciones de movimiento
void moveForward() {
  digitalWrite(pinAIN1, HIGH);       // Configurar dirección motor 1
  digitalWrite(pinAIN2, LOW);        // Configurar dirección motor 1
  digitalWrite(pinBIN1, HIGH);       // Configurar dirección motor 2
  digitalWrite(pinBIN2, LOW);        // Configurar dirección motor 2
  analogWrite(pinPWMA, motorSpeed);  // Establecer velocidad motor 1
  analogWrite(pinPWMB, motorSpeed);  // Establecer velocidad motor 2
}

void turnLeft() {
  digitalWrite(pinAIN1, LOW);        // Configurar dirección motor 1
  digitalWrite(pinAIN2, HIGH);       // Configurar dirección motor 1
  digitalWrite(pinBIN1, HIGH);       // Configurar dirección motor 2
  digitalWrite(pinBIN2, LOW);        // Configurar dirección motor 2
  analogWrite(pinPWMA, motorSpeed);  // Establecer velocidad motor 1
  analogWrite(pinPWMB, motorSpeed);  // Establecer velocidad motor 2
}

void turnRight() {
  digitalWrite(pinAIN1, HIGH);       // Configurar dirección motor 1
  digitalWrite(pinAIN2, LOW);        // Configurar dirección motor 1
  digitalWrite(pinBIN1, LOW);        // Configurar dirección motor 2
  digitalWrite(pinBIN2, HIGH);       // Configurar dirección motor 2
  analogWrite(pinPWMA, motorSpeed);  // Establecer velocidad motor 1
  analogWrite(pinPWMB, motorSpeed);  // Establecer velocidad motor 2
}

void stopMotors() {
  digitalWrite(pinAIN1, LOW);  // Detener motor 1
  digitalWrite(pinAIN2, LOW);  // Detener motor 1
  digitalWrite(pinBIN1, LOW);  // Detener motor 2
  digitalWrite(pinBIN2, LOW);  // Detener motor 2
}

// Función para medir la distancia con el sensor ultrasónico
void measureDistance() {
  digitalWrite(trigPin, LOW);                   // Iniciar la medición apagando el trigger
  delayMicroseconds(5);                         // Pequeña pausa
  digitalWrite(trigPin, HIGH);                  // Activar el pulso ultrasónico
  delayMicroseconds(15);                        // Pulso activo
  digitalWrite(trigPin, LOW);                   // Desactivar el pulso ultrasónico
  ultrasonicDuration = pulseIn(echoPin, HIGH);  // Medir la duración del eco
  distanceCm = ultrasonicDuration / 58;         // Calcular la distancia en centímetros
}

void setup() {
  pinMode(pinAIN1, OUTPUT);  // Configurar pines como salidas
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(5000);  // Esperar 5 segundos
}

void loop() {
  measureDistance();  // Realizar una medición ultrasónica

  if (distanceCm > 1 && distanceCm < 40) {
    ticCounter++;
  } else {
    ticCounter = 0;
  }

  if (ticCounter >= 2) {
    if (robotState == 0 && millis() > 5050) {
      turnRight();  // Girar a la derecha si el estado es 0 y ha pasado suficiente tiempo
      delay(10);
    }

    moveForward();  // Avanzar recto con la velocidad establecida
    delay(300);
    robotState = 1;  // Cambiar el estado a 1
  } else {
    turnLeft();    // Girar a la izquierda
    stopMotors();  // Detener los motores
  }
}
