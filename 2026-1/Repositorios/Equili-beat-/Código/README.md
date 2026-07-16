# 💻 Código y Firmware

Este directorio contiene el código fuente principal (`.ino`) ejecutado en el microcontrolador Arduino UNO para mantener el equilibrio dinámico del robot.

### Estructura del Lazo de Control
El código implementa un lazo cerrado que funciona a alta frecuencia:
1. Adquisición de datos desde el **MPU6050** (I2C).
2. Cálculo del ángulo actual filtrado.
3. Cálculo del error respecto al *Setpoint* (0 grados).
4. Algoritmo **PID** (Proporcional - Integral - Derivativo).
5. Mapeo a señales **PWM** hacia el driver L298N.

### Diagrama Lógico de Ejecución
A continuación se detalla el flujo de programación principal del sistema:

![Diagrama Lógica](diagrama_logica.png)
