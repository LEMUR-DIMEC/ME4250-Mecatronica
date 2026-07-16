/*
 * ==============================================================================
 * PROYECTO: Mini Robot Auto-Balancín "Equili-beat"
 * CURSO: Mecatrónica ME4250
 * ------------------------------------------------------------------------------
 * INTEGRANTES: 
 * - Antonia Muñoz
 * - María Jesús Caldera
 * - Benjamín Olivares
 * - Benjamín Bou
 * ------------------------------------------------------------------------------
 * DESCRIPCIÓN: Implementación de un lazo cerrado de control PID utilizando la
 * lectura filtrada del sensor MPU6050 a través de I2C y comandos de velocidad
 * PWM mediante el Driver L298N para motores DC.
 * ==============================================================================
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// ─── PINES DEL MOTOR ───────
const int IN1 = 3;  
const int IN2 = 4;  
const int ENA = 5;  // Velocidad Motor Izquierdo (PWM)
const int IN3 = 7;  
const int IN4 = 8;  
const int ENB = 6;  // Velocidad Motor Derecho (PWM)

// ─── VARIABLES DEL SENSOR Y FILTRO ─────────────
float angulo_final = 0;
unsigned long tiempo_anterior = 0;

// ─── CONTROL PID ─────────────────
float Kp = 35.0;       
float Ki = 3;       
float Kd = 0.7;       
float setpoint = 0.0; 

float error_previo = 0;
float integral = 0;

void setup() {
  Serial.begin(115200); 
  Wire.begin();
  
  // Configurar pines de motores como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configurar el LED interno de la placa Arduino (Pin 13)
  pinMode(LED_BUILTIN, OUTPUT); 

  // Inicializar sensor MPU-6050
  mpu.initialize();
  
  // ─── INICIO DE LA CALIBRACIÓN (2 SEGUNDOS) ───
  digitalWrite(LED_BUILTIN, HIGH); // PRENDER LED: Mantener robot derecho y quieto
  
  float suma_angulos = 0;
  int numero_lecturas = 100;
  
  for (int i = 0; i < numero_lecturas; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // Calcular ángulo estático inicial
    float angulo_estatico = atan2(ay, az) * 180.0 / PI;
    suma_angulos += angulo_estatico;
    delay(20); 
  }
  
  // Guardamos el promedio como el "Punto Cero" (setpoint de equilibrio)
  setpoint = suma_angulos / numero_lecturas;
  angulo_final = setpoint; 
  
  digitalWrite(LED_BUILTIN, LOW); // APAGAR LED: Terminó la calibración
  delay(1000); 

  tiempo_anterior = micros();
} 

void loop() {
  // 1. LEER LOS DATOS CRUDOS DEL SENSOR
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // 2. CALCULAR EL TIEMPO EXACTO TRANSCURRIDO (dt)
  unsigned long tiempo_actual = micros();
  float dt = (tiempo_actual - tiempo_anterior) / 1000000.0; 
  tiempo_anterior = tiempo_actual;

  // 3. FILTRO COMPLEMENTARIO CORREGIDO
  float angulo_acelerometro = atan2(ay, az) * 180.0 / PI;
  
  // Usamos gx para medir la caída sobre el eje de las ruedas
  float velocidad_giroscopio = gx / 131.0; 
  
  angulo_final = 0.98 * (angulo_final + velocidad_giroscopio * dt) + 0.02 * angulo_acelerometro;

  // 4. ALGORITMO DE CONTROL PID
  float error = setpoint - angulo_final;
  
  integral += error * dt;
  integral = constrain(integral, -400, 400); 
  
  float derivada = (error - error_previo) / dt;
  error_previo = error;

  float esfuerzo_pid = (Kp * error) + (Ki * integral) + (Kd * derivada);

  // 5. TRADUCIR EL ESFUERZO A MOVIMIENTO REAL
  moverMotores(esfuerzo_pid);

  Serial.println(angulo_final); 
  delay(10); 
} 

void moverMotores(float potencia) {
  // SISTEMA DE SEGURIDAD INTERNO (Se apaga si se cae más de 45 grados)
  if (angulo_final > 45 || angulo_final < -45) {
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW); 
    analogWrite(ENA, 0);
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, LOW); 
    analogWrite(ENB, 0);
    integral = 0; 
    return;
  }

  int pwm = abs(potencia);
  
  // ─── NUEVO: COMPENSACIÓN DE ZONA MUERTA ───
  // Le da un empujón inicial de 50 para vencer la fricción de los motores
  if (pwm > 0) {
    pwm = pwm + 50; 
  }
  
  // Aseguramos que no sobrepase el límite máximo de 255
  pwm = constrain(pwm, 0, 255);

  if (potencia > 0) { 
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
  } else {             
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);
  }
  
  analogWrite(ENA, pwm);
  analogWrite(ENB, pwm);
}
