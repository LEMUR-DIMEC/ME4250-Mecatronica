#include <Arduino.h>

// ====== Pines TCS3200 (GY-31) ======
const int S0 = A0;
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int OUT_PIN = 4;  // Salida de frecuencia

volatile unsigned long pulseCount = 0;

// --- ISR: contar flancos del OUT ---
void countPulse() {
  pulseCount++;
}

// Tiempo de muestreo en milisegundos
const unsigned long SAMPLE_MS = 100;

// --- Medición de frecuencia (Hz) ---
unsigned int measureFreq(uint8_t ch) {
  // Selección de filtro de color
  switch (ch) {
    case 0: digitalWrite(S2, LOW);  digitalWrite(S3, LOW);  break;  // R
    case 1: digitalWrite(S2, HIGH); digitalWrite(S3, HIGH); break;  // G
    case 2: digitalWrite(S2, LOW);  digitalWrite(S3, HIGH); break;  // B
  }

  pulseCount = 0;
  unsigned long t0 = millis();
  while (millis() - t0 < SAMPLE_MS) {
    // conteo dentro de la ventana temporal
  }
  unsigned int freq = (unsigned int)((pulseCount * 1000UL) / SAMPLE_MS);
  return freq;
}

void setup() {
  Serial.begin(115200);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  // Configuración de escala (~20%)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  attachInterrupt(digitalPinToInterrupt(OUT_PIN), countPulse, RISING);

  Serial.println("===== Calibración del Sensor TCS3200 =====");
  Serial.println("Coloca un objeto NEGRO o superficie OSCURA debajo del sensor.");
  Serial.println("Luego, presiona cualquier tecla en el monitor serie.");
  Serial.println();
}

void loop() {
  if (Serial.available()) {
    Serial.read(); // limpiar buffer

    // Medición para cada color
    unsigned int fR = measureFreq(0);
    unsigned int fG = measureFreq(1);
    unsigned int fB = measureFreq(2);

    Serial.println("Lectura actual:");
    Serial.print("R: "); Serial.print(fR);
    Serial.print(" | G: "); Serial.print(fG);
    Serial.print(" | B: "); Serial.println(fB);

    Serial.println("\nCambia el color de referencia (oscuro o blanco)");
    Serial.println("y presiona otra tecla para medir nuevamente.\n");

    delay(1000);
  }
}
