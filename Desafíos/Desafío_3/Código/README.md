# Desafío 3 Mecatrónica 🤖⚖️

¡Bienvenido al directorio de código! 🧠

Esta carpeta contiene el firmware necesario para operar el sistema **Ball and Beam**. El sistema utiliza un microcontrolador **Arduino** para gestionar la retroalimentación de sensores ultrasónicos, estabilizar el sistema mediante un algoritmo de control **PID** (Proporcional, Integral, Derivativo) e integrar una Interfaz Hombre-Máquina (HMI) con teclado matricial y pantalla LCD para ajustar las ganancias dinámicamente.

### 📂 Estructura de Carpetas

Aquí se muestra la organización de los archivos fuente incluidos en esta versión:

```text
Code v3
├── 📂 Calibration
│   └── 📜 Desafio_3_Calibration.ino      <-- (Utilidad) Calibrar límites del servomotor y testear sensores
├── 📜 Desafio_3_PID.ino                  <-- (Principal) Código de control PID y telemetría HMI (Desafío 3)
└── 📝 README.md                          <-- (Documentación) Estás aquí

```

### 🔌 Conexiones y Pinout

A continuación se muestra el mapeo de hardware específico definido en el código fuente de producción (`Desafio_3_PID.ino`). Asegúrate de que tus conexiones físicas coincidan estrictamente con estas definiciones para evitar fallos lógicos o colisiones mecánicas:

| Componente | Función Pin | Pin Arduino | Notas |
| --- | --- | --- | --- |
| **Servomotor** | PWM / Control | **D10** | Actuador principal del balancín (Restringido por seguridad) |
| **Ultrasónico 1 (Izquierdo)** | TRIG | **D11** | Emisor ultrasónico |
|  | ECHO | **D12** | Receptor ultrasónico |
| **Ultrasónico 2 (Derecho)** | TRIG | **A0** | Emisor ultrasónico (Uso analógico como pin digital) |
|  | ECHO | **A1** | Receptor ultrasónico (Uso analógico como pin digital) |
| **Teclado Matricial 4x4** | Filas (R1-R4) | **D9, D8, D7, D6** | Mapeo lógico de las filas del Keypad |
|  | Columnas (C1-C4) | **D5, D4, D3, D2** | Mapeo lógico de las columnas del Keypad |
| **Pantalla LCD I2C** | SDA / SCL | **A4 / A5** | Dirección I2C configurada en `0x27` (16x2) |

> **⚠️ Dependencias:** Debes instalar las librerías `LiquidCrystal_I2C.h`, `Keypad.h` y `Servo.h` a través del Gestor de Librerías de Arduino IDE antes de compilar.

### 🛠️ Flujo Metodológico de Ejecución

#### 1. Calibración Mecánica y Sensorial (`Desafio_3_Calibration.ino`)

Antes de ejecutar el algoritmo PID, es mandatorio calibrar el rango de movimiento seguro del servomotor y validar las lecturas espaciales de los sensores:

1. Carga el archivo `Desafio_3_Calibration.ino` en tu placa Arduino.
2. Abre el **Monitor Serie** configurado a **9600 baudios**.
3. **Calibración del Servo**: Modifica manualmente la variable `anguloCalibracion` en el código y súbelo iterativamente para encontrar el rango mecánico ideal de la biela. Determina tus constantes:
* `ANGULO_MIN` (Ej: 50°)
* `ANGULO_PIVOTE` (Ej: 90° - Viga perfectamente horizontal)
* `ANGULO_MAX` (Ej: 140°)


4. **Prueba Ultrasónica**: Coloca la pelota sobre la viga y verifica que las distancias reportadas por el "Sensor Izquierdo" y el "Sensor Derecho" en el Monitor Serie sean estables y no presenten rebotes extraños.

#### 2. Operación y Sintonización PID (`Desafio_3_PID.ino`)

1. Abre el archivo de producción principal: `Desafio_3_PID.ino`.
2. **Actualizar Límites de Calibración**: Dirígete a la sección 2 del código (Configuración del Sistema) e ingresa los ángulos descubiertos (`ANGULO_MIN`, `ANGULO_PIVOTE`, `ANGULO_MAX`), además de verificar tus límites de rango útil (`RANGO_MIN`, `RANGO_MAX`, `LONGITUD_VIGA`).
3. **Modo Debug (Telemetría en Vivo)**: Si deseas observar el error y la posición actual graficados en el Serial Plotter (a 115200 baudios), asegúrate de descomentar la macro `#define DEBUG_MODE 1` en la línea 3. Si vas a operar el robot de forma completamente autónoma, coméntala; esto evita que el buffer Serial cause bloqueos o retardos (*cuellos de botella*) en el tiempo de muestreo fijo de 50 ms de tu PID.
4. Carga el firmware en el microcontrolador.
5. **Sintonización Dinámica (HMI)**:
* Al iniciar, la interfaz entrará en estado **BLOQ** tras 10 segundos de inactividad por seguridad.
* Selecciona la ganancia a modificar presionando la tecla **A (Kp)**, **B (Ki)** o **C (Kd)**.
* Utiliza el teclado numérico para ingresar el valor deseado y el asterisco ***** como punto decimal.
* Aplica el nuevo valor en tiempo real presionando el numeral **#**. (Si te equivocas tipeando, usa la tecla **D** para limpiar el campo).


6. **Lógica "Anti-Fantasmas"**: El sistema cuenta con una función de lectura cruzada ponderada (60% lectura actual, 40% lectura histórica) para evitar mediciones congeladas o ruido ultrasónico cuando la pelota adquiere alta velocidad.
