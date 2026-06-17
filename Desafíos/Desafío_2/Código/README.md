# Desafío 2 Mecatrónica - Lógica y Programación 💻⚙️


¡Bienvenido al directorio de código! 🧠

Esta carpeta contiene el firmware necesario para operar la **Cinta Transportadora Clasificadora**. El sistema utiliza un microcontrolador **Arduino** para gestionar la lógica de alta precisión en detección de objetos, mapeo RGB de color y actuación electromecánica mediante un motor paso a paso y barreras de servomotores.

### 📂 Estructura de Carpetas

Aquí se muestra la organización de los archivos fuente incluidos en esta versión:

```text
Code v2
├── 📂 Calibration_TCS3200
│   └── 📜 Calibration_TCS3200.ino       <-- (Utilidad) Calibrar límites de ancho de pulso del sensor
├── 📜 Conveyor_Belt_D2_Student.ino      <-- (Principal) Código de producción para clasificación y evaluación (Desafío 2)
└── 📝 README.md                         <-- (Documentación) Estás aquí

```

### 🔌 Conexiones y Pinout

> **⚡ Diagrama Electrónico:**
> Para esquemas detallados, rutas de ruteo en la PCB personalizada y conexiones de regulación de potencia, por favor visita el módulo **Electronics v2**:
> 👉 **[Electronics v1 README](https://www.google.com/search?q=../Electronics%2520v2/README.md)**

A continuación se muestra el mapeo de hardware específico definido en el código fuente de producción (`Conveyor_Belt_D2_Student.ino`). Asegúrate de que tus conexiones físicas en la placa personalizada coincidan estrictamente con estas definiciones para evitar fallos de hardware:

| Componente | Función Pin | Pin Arduino | Notas |
| --- | --- | --- | --- |
| **EasyDriver A3967** | STEP | **D2** | Señal de pulsos de paso (Control AccelStepper) |
|  | DIR | **D3** | Señal de control de dirección |
| **TCS3200 (GY-31)** | S0 | **A0** | Selección de Escala de Frecuencia |
|  | S1 | **A1** | Selección de Escala de Frecuencia |
|  | S2 | **A2** | Selección Filtro de Fotodiodo de Color |
|  | S3 | **A3** | Selección Filtro de Fotodiodo de Color |
|  | OUT | **D4** | Entrada de ancho de pulso de señal (`pulseIn`) |
| **Servomotores** | Servo 1 | **D9** | Desvío de objetos (Restringido por seguridad) |
|  | Servo 2 | **D10** | Desvío de objetos (Restringido por seguridad) |

> **⚠️ Dependencias:** Debes instalar la librería `AccelStepper.h` a través del Gestor de Librerías de Arduino IDE, y verificar que `Servo.h` se encuentre disponible en tu entorno antes de compilar.

### 🛠️ Flujo Metodológico de Ejecución

#### 1. Calibración Ambiental del Sensor (`Calibration_TCS3200.ino`)

Antes de ejecutar la lógica de producción, es mandatorio determinar las respuestas en frecuencia del hardware bajo las condiciones lumínicas específicas del entorno:

1. Carga el archivo `Calibration_TCS3200.ino` en tu placa.
2. Abre el **Monitor Serie** configurado a **115200 baudios** (o la velocidad seteada en la utilidad).
3. Posiciona un objeto de referencia **Negro Mate** bajo la cámara oscura del sensor y registra los tiempos de ancho de pulso máximos.
4. Posiciona un objeto de referencia **Blanco Puro** cuando el sistema lo solicite y registra los tiempos de ancho de pulso mínimos.
5. **Anota los valores crudos** obtenidos para los canales independientes R, G y B.

#### 2. Operación de la Máquina Principal (`Conveyor_Belt_D2_Student.ino`)

1. Abre el archivo de producción principal: `Conveyor_Belt_D2_Student.ino`.
2. **Actualizar Límites de Calibración**: Dirígete a las líneas de configuración del Paso 2 e introduce los valores medidos en las constantes del firmware:
* `R_BLACK`, `G_BLACK`, `B_BLACK` (Métricas de tiempo para negro/tiempos largos).
* `R_WHITE`, `G_WHITE`, `B_WHITE` (Métricas de tiempo para blanco/tiempos cortos).


3. **Calibrar Umbrales de Clasificación**: Modifica las condiciones lógicas dentro de la función `clasificarRGB(r, g, b)` para que coincidan con los perfiles estándar mapeados (0-255) de tus objetos reales.
4. Carga el firmware modificado en el microcontrolador.
5. **Secuencia Dinámica**:
* **Fase de Búsqueda**: La correa avanza en pasos cortos controlados (`400 pasos`) buscando variaciones en el sensor.
* **Detección**: Al clasificar un color válido (Acción $\neq$ 0), el filtro de protección mecánica posiciona los servos dentro de rangos seguros ($45^\circ$ a $135^\circ$) previniendo colisiones mecánicas con el chasis.
* **Espera**: El proceso realiza un retraso controlado de **5 segundos** posterior a la detección.
* **Evacuación**: El motor paso a paso tracciona de forma continua durante **10 segundos** (`50000 pasos`) para despachar el objeto hacia su respectiva caja receptora.
* **Restablecimiento**: La correa se detiene con una rampa desacelerada y las palas retornan automáticamente a su ángulo seguro de descanso ($90^\circ$).

