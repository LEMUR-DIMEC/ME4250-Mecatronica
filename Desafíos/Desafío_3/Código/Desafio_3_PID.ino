// --- INTERRUPTOR DE MODO DEBUG ---
// Comenta la siguiente línea poniéndole // al principio para desactivar el Serial en todo el código
//define DEBUG_MODE 1 

#ifdef DEBUG_MODE
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// ==========================================
// 1. CONFIGURACIÓN DE PANTALLA Y TECLADO
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

char constanteSeleccionada = 'A';
String bufferEntrada = "";
unsigned long tiempoAnteriorBlink = 0;
const long intervaloBlink = 500;
bool estadoBlink = true;
unsigned long ultimoTiempoActividad = 0;
const unsigned long TIEMPO_BLOQUEO = 10000;
bool modoEdicion = false;

// ==========================================
// 2. CONFIGURACIÓN DEL SISTEMA BALL & BEAM
// ==========================================
Servo servoBalancin;
const int pinServo = 10; 

const int ANGULO_MIN = 50;
const int ANGULO_PIVOTE = 90; 
const int ANGULO_MAX = 140;

const int trig1 = 11;
const int echo1 = 12;
const int trig2 = A0;
const int echo2 = A1;

const float RANGO_MIN = 3.0;
const float RANGO_MAX = 41.0;
const float LONGITUD_VIGA = 44.0; 
float posicionPromedio = 22.0;    

// ==========================================
// 3. VARIABLES DEL CONTROL PID
// ==========================================
float Kp = 0.0, Ki = 0.0, Kd = 0.0;
float setpoint = 22.0; 
float errorAnterior = 0.0;
float errorIntegral = 0.0;

unsigned long tiempoAnteriorPID = 0;
const long intervaloPID = 50; // 50 ms

void setup() {
  // ATENCIÓN: Alta velocidad para no frenar el PID
  #ifdef DEBUG_MODE
    Serial.begin(115200); 
  #endif
  lcd.init();
  lcd.backlight();
  actualizarPantalla();

  servoBalancin.attach(pinServo);
  servoBalancin.write(ANGULO_PIVOTE);

  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
}

void loop() {
  unsigned long tiempoActual = millis();

  // ==========================================
  // BLOQUE A: LAZO DE CONTROL PID (50 ms)
  // ==========================================
  if (tiempoActual - tiempoAnteriorPID >= intervaloPID) {
    float dt = (tiempoActual - tiempoAnteriorPID) / 1000.0;
    tiempoAnteriorPID = tiempoActual;

    float posicionActual = leerPosicionAntiFantasmas();
    float error = setpoint - posicionActual;

    float P = Kp * error;

    errorIntegral += error * dt;
    errorIntegral = constrain(errorIntegral, -30.0, 30.0); 
    float I = Ki * errorIntegral;

    float derivada = (error - errorAnterior) / dt;
    float D = Kd * derivada;
    errorAnterior = error;

    float salidaPID = P + I + D;
    
    int anguloComando = ANGULO_PIVOTE + (int)salidaPID; 
    anguloComando = constrain(anguloComando, ANGULO_MIN, ANGULO_MAX);
    servoBalancin.write(anguloComando);

    // SECCIÓN DESCOMENTADA: Ahora podrás ver la telemetría en tiempo real
    DEBUG_PRINT("Pos:"); Serial.print(posicionActual); 
    DEBUG_PRINT("\tError:"); Serial.print(error);
    DEBUG_PRINT("\tAngulo:"); Serial.println(anguloComando);
  }

  // ==========================================
  // BLOQUE B: INTERFAZ HMI (KEYPAD + LCD)
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
        errorIntegral = 0; 
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

  if (modoEdicion && (tiempoActual - ultimoTiempoActividad >= TIEMPO_BLOQUEO)) {
    modoEdicion = false; bufferEntrada = ""; 
  }
  if (tiempoActual - tiempoAnteriorBlink >= intervaloBlink) {
    tiempoAnteriorBlink = tiempoActual; estadoBlink = !estadoBlink;
  }
  actualizarPantalla();
}

// ==========================================
// FUNCIONES DE CONTROL
// ==========================================

float leerPosicionAntiFantasmas() {
  int d1 = medirDistanciaSegura(trig1, echo1);
  int d2 = medirDistanciaSegura(trig2, echo2);

  float lecturaCruda = -1.0;

  if (d1 >= RANGO_MIN && d1 <= RANGO_MAX && d2 >= RANGO_MIN && d2 <= RANGO_MAX) {
    lecturaCruda = (d1 + (LONGITUD_VIGA - d2)) / 2.0;
  } else if (d1 >= RANGO_MIN && d1 <= RANGO_MAX) {
    lecturaCruda = d1;
  } else if (d2 >= RANGO_MIN && d2 <= RANGO_MAX) {
    lecturaCruda = LONGITUD_VIGA - d2;
  }

  if (lecturaCruda != -1.0) {
    float diferencia = lecturaCruda - posicionPromedio;

    if (abs(diferencia) > 6.0) {
      if (diferencia > 0) posicionPromedio += 1.5; 
      else posicionPromedio -= 1.5;
    } else {
      posicionPromedio = 0.6 * lecturaCruda + 0.4 * posicionPromedio;
    }
  }
  return posicionPromedio; 
}

int medirDistanciaSegura(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  // AUMENTADO A 6000us para dar más tiempo a que el eco rebote en la bola curva
  long duracion = pulseIn(pinEcho, HIGH, 6000); 
  
  if (duracion == 0) return -1; 
  return duracion * 0.034 / 2;
}

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