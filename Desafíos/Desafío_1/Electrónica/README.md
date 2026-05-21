# ⚡ Diseño Electrónico y PCB - El Ratmóvil

## ME4250 - Mecatrónica | Subcarpeta de Electrónica

Esta carpeta contiene la planimetría eléctrica y los archivos de fabricación de la placa de circuito impreso (PCB) personalizada para el Ratmóvil. El diseño ha sido optimizado para integrar la etapa de control lógico y la etapa de potencia en una sola estructura compacta y robusta.

---
## 🗺️ Diagrama Esquemático del Circuito

A continuación puede acceder al plano electrónico vectorizado en alta resolución. Haga clic en el siguiente enlace para abrir el documento técnico:

*📄 **[Plano_Esquematico_Ratmovil.pdf](../Electrónica/Esquem_tico_Desaf_o_1_ME4250.pdf)** - Esquema eléctrico completo con la distribución de conexiones del microcontrolador y la etapa de potencia.

---



## 🧩 Arquitectura de Componentes Internos

El circuito está diseñado considerando la separación virtual entre la lógica de 3.3V y el consumo de alta corriente de los motores. Los componentes principales ruteados en la placa son:

* **Microcontrolador (ESP32 NodeMCU):** Actúa como el cerebro del sistema. Recibe alimentación y distribuye las señales de control (PWM y lógica digital) hacia el driver y los LEDs.
* **Driver de Motores (TB6612FNG):** Un puente H dual basado en MOSFETs, mucho más eficiente que el clásico L298N. Recibe las señales lógicas de la ESP32 y conmuta el voltaje de las baterías para accionar los 2 motores DC amarillos.
* **Gestión de Energía (Baterías y Switch):** La entrada principal de energía proviene de 2 baterías Ion-Litio 18650 (aprox. 7.4V - 8.4V). El circuito pasa obligatoriamente por un **switch de 3 pines** de corte general para energizar o desenergizar todo el sistema de forma segura.
* **Señalización Visual (4x LEDs):** Ruteados directamente a los pines GPIO de la ESP32, cada uno acompañado de su respectiva resistencia limitadora de corriente para proteger el microcontrolador.

---

## 🖨️ Archivos Gerber y Especificaciones de Ruteo

Para facilitar la inspección técnica o la manufactura directa de la placa en fábricas especializadas (como JLCPCB o PCBWay), en esta carpeta se incluyen los **Archivos Gerber** comprimidos.

### Especificaciones Técnicas de la PCB:

* **Ancho de Pista (Trace Width) Estándar:** **0.254 mm** (10 mils). Este grosor fue seleccionado para garantizar un ruteo denso y seguro para las señales lógicas y de control entre la ESP32 y el driver, cumpliendo con los estándares de manufactura de bajo costo sin riesgo de cortes en el cobre.
* **Planos de Tierra (GND):** Las tierras de la lógica (ESP32) y la potencia (Baterías/Motores) están unificadas en la placa para establecer una referencia de voltaje común, evitando que el ruido electromagnético desestabilice el firmware.
