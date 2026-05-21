# 📄 Documentación y Guías - El Ratmóvil

## ME4250 - Mecatrónica | Subcarpeta de Documentos

Esta carpeta centraliza los archivos de oficina, presentaciones y guías formales necesarias para comprender los objetivos técnicos y administrativos del primer desafío del curso. Es el punto de partida recomendado para todos los integrantes del equipo antes de interactuar con los componentes físicos o el código fuente.

---

## 📚 Contenido del Directorio

A continuación se detallan los documentos principales incluidos en esta sección y su propósito dentro del ciclo de desarrollo:

### 1. Guía de Configuración del Entorno de Software

* **`Desafío_1_Parte_1.pdf`**
Este documento es un manual técnico paso a paso, indispensable para la preparación del entorno de programación. Contiene las instrucciones precisas para:
* Instalar **Visual Studio Code**.
* Configurar la extensión **PlatformIO**.
* Reconocer el puerto serial y establecer la primera comunicación exitosa con el microcontrolador **ESP32** que da vida al Ratmóvil.



### 2. Enunciado y Reglas del Desafío

* **`Enunciado_Desafío_1.pdf`** *(o archivo de presentación PPTX asociado)*
Este documento engloba el marco teórico y práctico de la evaluación, detallando el contexto de la liga de carreras "Fast & Rats" y qué se espera mecánicamente del piloto (tracción diferencial, giros y señalización visual).

---

## 📊 Rúbrica de Evaluación y Recomendaciones

> 💡 **Consejo de Ingeniería:** Revisen minuciosamente la rúbrica de evaluación *antes* de comenzar a programar y *durante* las pruebas en pista. En la mecatrónica, es común que los equipos se enfoquen exclusivamente en lograr que el robot se mueva, olvidando documentar el firmware o generar el esquemático eléctrico, perdiendo puntos valiosos en entregables de fácil cumplimiento.

A continuación se presenta el desglose oficial de los criterios de evaluación del Desafío 1 para asegurar el correcto desarrollo de todos los hitos de hardware, firmware y documentación del reporte:

| Criterio | Descripción | Puntaje |
| --- | --- | --- |
| **Diagrama esquemático** | Entrega de un diagrama esquemático detallado de la arquitectura de conexiones del Desafío 1. Debe ser incorporado directamente en el reporte formal. | 1.0 pto |
| **Código comentado** | Código fuente en C++ utilizado durante el desafío, estructurado de forma limpia y bien comentado paso a paso. Se debe adjuntar al reporte para su revisión. | 1.0 pto |
| **Funciones LEDs y motores** | Implementación de lógica modular y funciones esenciales que permitan el correcto accionamiento de los motores y el encendido sincronizado de los LEDs. Los LEDs deben señalizar de forma obligatoria el movimiento hacia: adelante, atrás, izquierda y derecha. | 1.0 pto |
| **Rutina remota / Circuito** | Completar satisfactoriamente el circuito en la pista de pruebas. Se puede lograr mediante una rutina de movimientos autónomos preestablecida en la máquina de estados o utilizando el servidor de control remoto vía Wi-Fi. | 2.0 ptos |
| **Propuestas de mejora** | Inclusión de una sección crítica en el reporte que detalle mejoras u observaciones del Desafío 1 en relación a su nivel de dificultad, metodología de trabajo o aprendizajes significativos. | 1.0 pto |
| **Total Máximo** | **Evaluación Integral del Desafío 1 - "Fast & Rats"** | **6.0 ptos** |
