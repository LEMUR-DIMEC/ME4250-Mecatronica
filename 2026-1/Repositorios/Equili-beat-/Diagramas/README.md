# 🔌 Diagramas Electrónicos y de Control

En esta sección se documenta la arquitectura de hardware y la teoría de control implementada en el robot.

### Diagrama de Conexiones (Pinout)
La distribución de señales entre el Arduino y la etapa de potencia (Driver L298N) se configuró de la siguiente manera:
* `ENA` = Pin 5 (PWM Motor Izquierdo)
* `IN1` = Pin 3
* `IN2` = Pin 4
* `ENB` = Pin 6 (PWM Motor Derecho)
* `IN3` = Pin 7
* `IN4` = Pin 8

### Esquemático Electrónico
Representación visual del cableado entre el microcontrolador, el sensor inercial y el puente H:

![Diagrama Electronico](IMG_0578.jpeg)
