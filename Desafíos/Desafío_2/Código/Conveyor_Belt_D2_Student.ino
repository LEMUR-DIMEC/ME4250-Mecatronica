/*
 * DESAFÍO 2 - Sorting por Color (TCS3200 + NEMA/EasyDriver)
 * * PASOS A SEGUIR EN LA EVALUACIÓN:
 * 1- Usar código Calibration_TCS3200 y encontrar los límites.
 * 2- Pegar los límites de tiempo en las constantes correspondientes.
 * 3- Verificar calibración correcta y establecer los límites para la detección de colores.
 * 4- Programar la rutina con servomotores para desviar el objeto resguardando los límites mecánicos.
 * 5- Mover la correa en pasos cortos hasta detectar variación, esperar 5s y evacuar por 10s.
 */

#include <Servo.h>
#include <AccelStepper.h>

// ====== PINES ======
// Stepper (HW-135 / EasyDriver)
const int pinStep = 2;
const int pinDir  = 3;

// Sensor GY-31 (TCS3200)
const int S0 = A0;
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int SENSOR_OUT = 4;

// Servos
const int pinServo1 = 9;
const int pinServo2 = 10;

// ====== LÍMITES MECÁNICOS ======
const int ANGULO_DESCANSO = 90;
const int ANGULO_MIN = 45;
const int ANGULO_MAX = 135;

// ====== OBJETOS ======
AccelStepper motorCorrea(1, pinStep, pinDir);
Servo servo1;
Servo servo2;

// ====== PASO 2: LÍMITES DE CALIBRACIÓN ======
// TODO: Pegar aquí los valores de tiempo medidos en la calibración
// (Nota: Negro = Tiempos largos, Blanco = Tiempos cortos)
const unsigned long R_BLACK = 600; 
const unsigned long G_BLACK = 600; 
const unsigned long B_BLACK = 600; 

const unsigned long R_WHITE = 40; 
const unsigned long G_WHITE = 40; 
const unsigned long B_WHITE = 40; 

void setup() {
  Serial.begin(9600);

  // Configuración Sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
  
  // Escala de frecuencia al 100%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  // Configuración Servos
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  
  // Seteo inicial seguro en posición de descanso (90°)
  moverServosSeguro(ANGULO_DESCANSO);

  // Configuración Dinámica de la Correa
  motorCorrea.setMaxSpeed(800.0);
  motorCorrea.setAcceleration(300.0);

  delay(2000);
}

void loop() {
  // PASO 5 (Inicio): Mover la correa en pasos cortos para búsqueda de objetos
  motorCorrea.move(400); 
  motorCorrea.runToPosition();
  delay(200); 

  // Leer canales del sensor
  unsigned long tR = leerColor(LOW, LOW);
  unsigned long tG = leerColor(HIGH, HIGH);
  unsigned long tB = leerColor(LOW, HIGH);

  // Mapear tiempos a escala estándar RGB 0-255
  int R = mapInvertidoConstrain(tR, R_BLACK, R_WHITE);
  int G = mapInvertidoConstrain(tG, G_BLACK, G_WHITE);
  int B = mapInvertidoConstrain(tB, B_BLACK, B_WHITE);

  // Clasificar color actual
  int accion = clasificarRGB(R, G, B);

  // Depuración en Monitor Serie
  Serial.print("R:"); Serial.print(R);
  Serial.print(" G:"); Serial.print(G);
  Serial.print(" B:"); Serial.print(B);
  Serial.print(" | Accion: "); Serial.println(accion);

  // Si se detecta una variación de color válida (distinta al fondo)
  if (accion != 0) {
    
    // PASO 4: Rutina con servomotores aplicando límites de seguridad
    switch (accion) {
      case 1:
        Serial.println("Clasificación (1): Direccionando a Caja 1 (90°)");
        moverServosSeguro(90);
        break;

      case 2:
        Serial.println("Clasificación (2): Direccionando a Caja 2 (45°)");
        moverServosSeguro(45);
        break;

      case 3:
        Serial.println("Clasificación (3): Direccionando a Caja 3 (135°)");
        moverServosSeguro(135);
        break;
    }

    // PASO 5 (Medio): Esperar 5 segundos tras detectar la variación y accionar servos
    delay(5000);

    // PASO 5 (Fin): Mover continuamente por 10 segundos para evacuar el objeto
    Serial.println("Moviendo continuamente por 10s...");
    motorCorrea.move(50000L); 
    
    unsigned long tiempoInicio = millis();
    while (millis() - tiempoInicio < 10000) {
      motorCorrea.run();
    }
    
    // Detención controlada de la correa
    motorCorrea.stop();
    while (motorCorrea.distanceToGo() != 0) {
      motorCorrea.run();
    }
    
    // Retorno automático de servomotores a su ángulo inicial de descanso
    Serial.println("Retornando palas a posición de descanso (90°)");
    moverServosSeguro(ANGULO_DESCANSO);
  }
}

// ====== FUNCIONES AUXILIARES ======

/*
 * Función: moverServosSeguro
 * Parámetros: int angulo
 * Descripción: Filtra el ángulo solicitado a través de un rango restrictivo
 * para impedir colisiones mecánicas del chasis (45° a 135°).
 */
void moverServosSeguro(int angulo) {
  int anguloProtegido = constrain(angulo, ANGULO_MIN, ANGULO_MAX);
  servo1.write(anguloProtegido);
  servo2.write(anguloProtegido);
}

unsigned long leerColor(bool s2State, bool s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  delayMicroseconds(300);
  unsigned long t = pulseIn(SENSOR_OUT, LOW, 25000UL); 
  return t;
}

int mapInvertidoConstrain(unsigned long t, unsigned long t_black, unsigned long t_white) {
  long val = map(t, t_white, t_black, 255, 0); 
  if (val < 0) val = 0;
  if (val > 255) val = 255;
  return (int)val;
}

// PASO 3: Verificar calibración y establecer límites de detección
int clasificarRGB(int r, int g, int b) {
  // TODO: Ajustar los márgenes lógicos según las lecturas reales del entorno
  
  // Ejemplo: Detección de color predominantemente ROJO -> Caja 1
  if (r > 180 && g < 100 && b < 100) {
    return 1; 
  }
  
  // Ejemplo: Detección de color predominantemente VERDE -> Caja 2
  else if (r < 100 && g > 180 && b < 130) {
    return 2; 
  }

  // Ejemplo: Detección de color predominantemente AZUL -> Caja 3
  else if (r < 100 && g < 130 && b > 180) {
    return 3; 
  }

  return 0; 
}