#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h> // NUEVO: Librería para el servomotor

// ==========================================
// CONFIGURACIÓN DE PANTALLA Y TECLADO (HMI)
// ==========================================
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

float Kp = 0.0, Ki = 0.0, Kd = 0.0;
char constanteSeleccionada = 'A';
String bufferEntrada = "";

unsigned long tiempoAnteriorBlink = 0;
const long intervaloBlink = 500;
bool estadoBlink = true;

unsigned long ultimoTiempoActividad = 0;
const unsigned long TIEMPO_BLOQUEO = 10000;
bool modoEdicion = false;

// ==========================================
// CONFIGURACIÓN DE SENSORES Y SERVO (TEST)
// ==========================================
Servo servoBallAndBeam;
const int pinServo = 10; 

// ---> CALIBRACIÓN MANUAL AQUÍ <---
// Cambia este valor, sube el código y observa la posición de tu biela
// Pivote = 90°
// angulo max = 140
// angulo min = 50
int anguloCalibracion = 140; 

// Sensores Ultrasónicos (Cambiamos 0 y 1 por A0 y A1 por seguridad)
const int trig1 = 11;
const int echo1 = 12;
const int trig2 = A0;
const int echo2 = A1;

// Temporizador para el Monitor Serie
unsigned long tiempoAnteriorSerial = 0;

void setup() {
  // Iniciar comunicación Serial para ver los datos de los sensores
  Serial.begin(9600); 
  Serial.println("Iniciando Calibracion Ball and Beam...");

  // Inicializar HMI
  lcd.init();
  lcd.backlight();
  actualizarPantalla();

  // Inicializar Servo
  servoBallAndBeam.attach(pinServo);

  // Inicializar Pines de Ultrasónicos
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  unsigned long tiempoActual = millis();

  // ==========================================
  // BLOQUE 1: PRUEBA MANUAL DE SENSORES Y SERVO
  // ==========================================
  
  // 1. Escribimos el ángulo fijo al servo constantemente
  servoBallAndBeam.write(anguloCalibracion);

  // 2. Imprimimos los datos de los sensores en el Monitor Serie cada 500ms
  // Lo hacemos con temporizador para no saturar la placa ni afectar el teclado
  if (tiempoActual - tiempoAnteriorSerial >= 500) {
    tiempoAnteriorSerial = tiempoActual;
    
    int distancia1 = medirDistancia(trig1, echo1);
    int distancia2 = medirDistancia(trig2, echo2);

    Serial.print("Sensor Izquierdo: ");
    Serial.print(distancia1);
    Serial.print(" cm  |  Sensor Derecho: ");
    Serial.print(distancia2);
    Serial.println(" cm");
  }


  // ==========================================
  // BLOQUE 2: LÓGICA DE INTERFAZ (LCD + KEYPAD)
  // ==========================================
  char key = keypad.getKey();

  if (key) {
    ultimoTiempoActividad = tiempoActual; 

    if (key == 'A' || key == 'B' || key == 'C') {
      constanteSeleccionada = key;
      bufferEntrada = ""; 
      modoEdicion = true; 
    } 
    else if (modoEdicion) {
      if (key >= '0' && key <= '9') {
        bufferEntrada += key; 
      } 
      else if (key == '*') {
        if (bufferEntrada.indexOf('.') == -1) bufferEntrada += '.'; 
      } 
      else if (key == 'D') {
        bufferEntrada = ""; 
        if (constanteSeleccionada == 'A') Kp = 0.0;
        else if (constanteSeleccionada == 'B') Ki = 0.0;
        else if (constanteSeleccionada == 'C') Kd = 0.0;
      } 
      else if (key == '#') {
        if (bufferEntrada.length() > 0) {
          float valor = bufferEntrada.toFloat();
          if (constanteSeleccionada == 'A') Kp = valor;
          else if (constanteSeleccionada == 'B') Ki = valor;
          else if (constanteSeleccionada == 'C') Kd = valor;
          
          bufferEntrada = ""; 
          modoEdicion = false; 
        }
      }
    }
  }

  // Timeout y Parpadeo de la Interfaz
  if (modoEdicion && (tiempoActual - ultimoTiempoActividad >= TIEMPO_BLOQUEO)) {
    modoEdicion = false;
    bufferEntrada = ""; 
  }

  if (tiempoActual - tiempoAnteriorBlink >= intervaloBlink) {
    tiempoAnteriorBlink = tiempoActual;
    estadoBlink = !estadoBlink;
  }

  actualizarPantalla();
}

// ==========================================
// FUNCIONES AUXILIARES
// ==========================================

// Función para leer los ultrasonidos de forma segura
int medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  // El "Timeout" de 30000 microsegundos evita que la placa se congele 
  // si el sensor no detecta nada (límite de ~5 metros)
  long duracion = pulseIn(pinEcho, HIGH, 30000); 
  
  if (duracion == 0) return -1; // Retorna -1 si hay error o fuera de rango
  
  int distancia = duracion * 0.034 / 2;
  return distancia;
}

// Funciones del LCD (Sin cambios)
void actualizarPantalla() {
  lcd.setCursor(0, 0); lcd.print("P:"); mostrarValorBlink('A', Kp);
  lcd.setCursor(8, 0); lcd.print("I:"); mostrarValorBlink('B', Ki);
  lcd.setCursor(0, 1); lcd.print("D:"); mostrarValorBlink('C', Kd);

  lcd.setCursor(8, 1);
  if (modoEdicion) {
    lcd.print(">"); lcd.print(bufferEntrada);
  } else {
    lcd.print("BLOQ");
  }
  for(int i = (modoEdicion ? bufferEntrada.length() + 1 : 4); i < 8; i++) lcd.print(" ");
}

void mostrarValorBlink(char idConstante, float valor) {
  if (modoEdicion && constanteSeleccionada == idConstante && !estadoBlink) {
    lcd.print("    "); 
  } else {
    lcd.print(valor);
  }
  lcd.print(" "); 
}