# Desafío 2 Mecatrónica - Electrónica y Cableado ⚡🔌

¡Bienvenido al directorio de electrónica! 🔋

Esta sección cubre el "sistema nervioso" físico y la arquitectura de circuitos de la **Cinta Transportadora Clasificadora V2**. En esta versión, el cableado por jumpers punto a punto ha sido reemplazado por una **Placa de Circuito Impreso (PCB) Personalizada** para mejorar la confiabilidad estructural, mitigar la interferencia electromagnética (EMI) y centralizar los acoples modulares.

### 📂 Archivos de Manufactura Disponibles
Dentro de este directorio, se encuentran los archivos necesarios para la fabricación del hardware:
* 📁 **`Gerber_Files_V2.zip`**: Conjunto de archivos de fotoploteo de producción en formato estándar Gerber RS-274X para el fresado CNC físico o manufactura externa de la PCB.
* 📦 **`Project_EasyEDA_V2.zip`**: Paquete nativo del proyecto compatible con EasyEDA para modificaciones de hardware, edición de esquemáticos y ruteo de pistas.

* 📦 **`Esquem_tico_Desaf_o_2_ME4250.pdf`**: Plano esquemático de la PCB y la electrónica utilizada en la correa transportadora.

### 📜 Lista de Verificación de Componentes
Estos son los componentes electrónicos principales integrados en el diseño de la placa personalizada:
* **Microcontrolador:** Arduino Uno/Nano (Unidad de procesamiento lógico central).
* **Actuadores:**
    * 1x Motor Paso a Paso NEMA 17 (Unidad principal de tracción de precisión).
    * 1x Módulo Driver EasyDriver A3967 (Controlador de micropasos).
    * 2x Servomotores SG90 (Aletas dinámicas de clasificación).
* **Sensores:**
    * 1x TCS3200 / GY-31 (Sensor de Color RGB).
* **Regulación de Energía y Protección:**
    * 3x Baterías Li-Ion 18650 (Línea de potencia de entrada de ~11.1V - 12.6V).
    * 1x Regulador Convertidor Buck DC-DC Step-Down LM2596 (Regulador de voltaje lógico a 5V).
    * 1x Condensador Electrolítico de 470µF (Elemento de filtrado y desacople en la línea).
    * 1x Interruptor SPST de 2 pines.

---

### 🗺️ Diagrama Electrónico y Especificaciones de la PCB

> **📄 VER DIAGRAMA:**
> Por favor, abre el archivo PDF adjunto **`Esquematico_Desafio_2_ME4250.pdf`** en esta carpeta para examinar las redes de componentes, los encapsulados y los planos de ruteo interno.

* **Restricciones Técnicas de la PCB:** * **Color de Antisolder:** Verde industrial con serigrafía amarilla de alta definición para la identificación de pines, componentes y créditos del desarrollador.
  * **Vias y Perforaciones (Drills):** Tamaño estándar para señales lógicas (0.254 mm / 10 mil).
  * **Ancho de Pistas:** Las pistas estándar de señal lógica están ruteadas a **0.4 mm**. Las líneas de potencia que manejan alta corriente (VCC, salidas de motor y pines del regulador) se ensancharon a **0.6 mm** para soportar transitorios de corriente sin calentamiento del cobre.

---

### 🔌 Guía de Cableado y Mapa de Pines (Pinout)

Asegúrate de que los arneses de cables modulares (usando terminales XH2.54) coincidan con esta matriz de definición de hardware grabada en el diseño de la PCB:

| Componente | Etiqueta de Pin | Conexión Pin Arduino | Descripción |
| :--- | :--- | :---: | :--- |
| **EasyDriver A3967** | STEP | **D2** | Señal de Comando de Pulso de Paso |
| | DIR | **D3** | Nivel de Control de Dirección |
| **TCS3200 (GY-31)** | S0, S1 | **A0, A1** | Escalamiento de Frecuencia de Salida |
| | S2, S3 | **A2, A3** | Selección de Matriz de Fotodiodos de Color |
| | OUT | **D4** | Entrada de Ancho de Pulso de Frecuencia |
| **Servos (SG90)** | PWM_SG90_1 | **D9** | Señal de Control Actuador Aleta 1 |
| | PWM_SG90_2 | **D10** | Señal de Control Actuador Aleta 2 |

---

### ⚠️ Nota Crítica de Ingeniería: Anomalía de Tierra Común

> **🛠️ OBSERVACIÓN DE REVISIÓN DE HARDWARE:**
> Durante el ruteo de las pistas del esquemático `Desafio_2_v2`, se introdujo una leve discrepancia de diseño en el camino de retorno lógico:
> * **El Problema:** La conexión de la red principal de `GND` hacia el Arduino quedó vinculada a través de un pin de terminal destinado directamente al **bloque del regulador LM2596**, en lugar de establecerse en un pin de tierra digital independiente y aislado en el header principal del Arduino.
> * **Impacto Conductual:** Aunque existe continuidad eléctrica global con el terminal negativo del pack de baterías 18650, las corrientes de retorno intensas de las etapas de conmutación del motor paso a paso pueden acoplar ruido eléctrico en las líneas de tierra lógicas del microcontrolador.
> * **Requerimiento para Futuras Iteraciones V3:** Los próximos rediseños deben integrar obligatoriamente una fila dedicada e independiente de pines headers de distribución `GND` conectados mediante una geometría de tierra en estrella (*star ground*) para salvaguardar la integridad de la señal.
