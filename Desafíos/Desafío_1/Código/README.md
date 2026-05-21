# 💻 Firmware y Control - El Ratmóvil

## ME4250 - Mecatrónica | Subcarpeta de Código

Esta carpeta contiene el código fuente en C++ desarrollado para el microcontrolador ESP32. El firmware implementa el control diferencial de los motores a través de PWM, la lógica de señalización visual mediante LEDs y un servidor web integrado para telemetría y control remoto.

---

## 🚀 Preparación del Entorno (Requisitos Previos)

Antes de compilar y subir el código a la placa, por favor revisen el documento **`Desafío_1_Parte_1.pdf`** ubicado en la carpeta **[`../Documentos/`](https://www.google.com/search?q=../Documentos/)**. Allí encontrarán las instrucciones detalladas paso a paso para configurar **Visual Studio Code** junto con la extensión **PlatformIO**.

### Consideraciones Críticas de Hardware

* ⚠️ **Driver USB a UART (CP210x):** Si al intentar subir el código PlatformIO falla y no logra reconocer el puerto de su ESP32, es probable que a su sistema operativo le falte el controlador USB. Deben descargar e instalar el **Driver CP210x de Silicon Labs** para habilitar la comunicación serial.
* 🔌 **Alimentación Desconectada:** Al conectar el ESP32 por cable USB al computador para cargar el código, asegúrense rigurosamente de que el interruptor principal de las baterías del Ratmóvil esté **APAGADO**. Subir código con el circuito de potencia activo puede generar bucles de tierra o dañar el regulador de voltaje de la placa.

---

## 🧠 Arquitectura del Código (`D1_Master.cpp`)

El código principal está estructurado de manera modular para facilitar su escalabilidad durante el semestre. A continuación, se detallan las secciones y funciones principales:

### 1. Inicialización y Hardware (`initMotors`, `initLEDs`)

* Asigna los pines físicos de la ESP32 a las entradas del driver TB6612FNG y a los LEDs indicadores.
* Configura los canales **PWM (Pulse Width Modulation)** utilizando la API de hardware nativa del ESP32 (`ledcSetup`, `ledcAttachPin`). Esto permite variar el voltaje promedio enviado a los motores para controlar su velocidad de forma fluida.

### 2. Locomoción y Control de Movimiento (`motorsForward`, `motorsLeft`, etc.)

* Estas funciones definen la cinemática del robot. Establecen la combinación lógica (`HIGH`/`LOW`) en los pines `IN1` e `IN2` de cada motor para dictar su sentido de giro (marcha adelante, reversa o pivoteo sobre su propio eje).
* Se incluye una función `motorsBrake()` que pone en corto las bobinas de los motores para un frenado brusco y activo, a diferencia de `motorsStop()`, que libera los motores dejándolos detenerse por inercia.

### 3. Servidor Web y Control Remoto (`setupWiFi`, `setupRouting`)

* El microcontrolador se configura en modo **Punto de Acceso (Access Point)**, creando su propia red Wi-Fi independiente.
* Usando la librería `WebServer.h`, se definen endpoints o rutas HTTP (como `/forward`, `/stop`, `/speed`, `/blinkLeft`). Cuando un cliente (como un celular) accede a estas rutas, el robot procesa el string y ejecuta la función mecánica asociada.

### 4. Máquina de Estados (`loop`)

* Para garantizar que el control remoto responda en tiempo real, se erradicó el uso de retardos convencionales (`delay()`). En su lugar, el bucle principal utiliza **`millis()`** para crear una máquina de estados no bloqueante.
* Esto permite, por ejemplo, que los intermitentes laterales (`blinkLeft` / `blinkRight`) parpadeen dinámicamente de forma asíncrona, mientras la ESP32 sigue procesando los comandos entrantes del servidor web sin interrupción.
