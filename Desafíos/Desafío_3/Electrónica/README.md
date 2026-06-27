# Desafío 3 Mecatrónica - Electrónica y Cableado ⚡🔌

¡Bienvenido al directorio de documentación electrónica! 🔋

Esta sección cubre el esquema físico de potencia, la distribución de voltaje y la arquitectura eléctrica desarrollada para el sistema **Ball and Beam**. Para esta iteración, el sistema se enfoca en separar la alimentación en dos caminos distintos para satisfacer la alta demanda de energía del motor, protegiendo así al cerebro del robot (Arduino) y a sus sensores.

### 📂 Archivo de Documentación Disponible

Dentro de este directorio se encuentra el plano unificado para la conexión del hardware:

* 📜 **`Desafío 3 - Circuito.pdf`**: Plano esquemático simple que detalla las interconexiones, la distribución de voltajes (5V y 6V) y los componentes del sistema.

### 📜 Lista de Verificación de Componentes

Los siguientes módulos componen el circuito detallado en el plano esquemático:

* **Microcontrolador Central:** Arduino Uno R3 (Procesamiento del control PID).
* **Actuador de Potencia:**
* 1x Servomotor de Alto Torque **MG995** (Mueve el balancín).


* **Sensores:**
* 2x Sensores Ultrasónicos **HC-SR04** (Miden la posición de la bola).


* **Interfaz de Usuario (HMI):**
* 1x Pantalla LCD 16x2 con módulo **I2C**.
* 1x Teclado Matricial 4x4 (Para ingresar los valores del PID).


* **Energía:**
* 1x Fuente de Alimentación / Batería (~7.4V - 12V).
* 1x Regulador de voltaje (Configurado a **6.0V** para el servo).
* 2x Condensadores electrolíticos (Para filtrar ruidos eléctricos).



---

### 🔌 Guía de Cableado y Mapa de Pines

Asegúrate de que todas las conexiones físicas sigan estrictamente el siguiente orden para evitar cortocircuitos o fallos en el código:

| Componente | Pin del Módulo | Pin Arduino | Voltaje | Descripción |
| --- | --- | --- | --- | --- |
| **Servo MG995** | PWM / Señal | **D10** | **6.0V** | Control del ángulo del motor |
| **Ultrasonido 1 (Izq)** | TRIG | **D11** | **5.0V** | Emisor del pulso izquierdo |
|  | ECHO | **D12** | **5.0V** | Receptor del eco izquierdo |
| **Ultrasonido 2 (Der)** | TRIG | **A0** | **5.0V** | Emisor del pulso derecho |
|  | ECHO | **A1** | **5.0V** | Receptor del eco derecho |
| **Teclado 4x4** | Filas (R1-R4) | **D9, D8, D7, D6** | **5.0V** | Pines de las filas |
|  | Columnas (C1-C4) | **D5, D4, D3, D2** | **5.0V** | Pines de las columnas |
| **Pantalla LCD** | SDA | **A4** | **5.0V** | Datos I2C |
|  | SCL | **A5** | **5.0V** | Reloj I2C |

---

### ⚠️ Nota Crítica: 

> **🛠️ CONSIDERACIÓN DE DISEÑO:**
> * El servomotor MG995 es potente. Cuando el código le ordena cambiar de dirección bruscamente para estabilizar la bola, el motor consume muchísima energía de golpe. Si conectamos este motor a los mismos **5.0V** que el Arduino y los sensores, les "robará" la corriente. Esto hará que los sensores midan mal o que el Arduino se apague y se reinicie solo.
> * **La Solución:** Dividimos la energía. Usamos un regulador externo ajustado a **6.0V exclusivos para darle fuerza al motor**. Por otro lado, la energía limpia de **5.0V** del Arduino se usa únicamente para los sensores y la pantalla. Finalmente, unimos todos los cables negativos (`GND` o Tierra).
> 
> 
