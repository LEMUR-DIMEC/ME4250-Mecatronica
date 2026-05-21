# 📐 Modelado 3D y CAD - El Ratmóvil

## ME4250 - Mecatrónica | Subcarpeta de Hardware

Esta carpeta contiene los modelos geométricos tridimensionales del chasis y los componentes del Ratmóvil. Con el fin de simplificar la replicación y evitar errores de alineación física, se han dispuesto archivos de **ensamble completo**. Al abrirlos o importarlos en su software CAD, dispondrán de todas las piezas posicionadas correctamente en un único entorno de trabajo.

---

## 📦 Formatos Disponibles

El ensamble completo del robot se encuentra en los siguientes dos formatos estándar:

1. **`Ratmovil_Assembly.f3z` (Formato Nativo de Autodesk Fusion 360):**
* **Uso:** Recomendado si trabajas con Fusion 360.
* **Ventaja:** Conserva la estructura de componentes distribuidos, los enlaces entre piezas, las uniones mecánicas (*joints*) y facilita la modificación paramétrica directa del chasis de la PCB.


2. **`Ratmovil_Assembly.step` (Formato Interoperable Estándar):**
* **Uso:** Recomendado si utilizas cualquier otro software de diseño (SolidWorks, Inventor, Rhino, FreeCAD, etc.).
* **Ventaja:** Formato sólido universal (ISO 10303) que mantiene la geometría exacta y volumétrica de todo el conjunto de componentes sin importar la plataforma.



---

## 🛠️ Componentes Incluidos en el Ensamble

Al abrir cualquiera de los dos archivos, verás la integración espacial exacta de:

* Chasis base y soportes mecánicos personalizados.
* Modelos de referencia del hardware comercial: 2x Motores DC amarillos con *gearbox*, 1x rueda loca de base 4cm, 1x portapilas 18650 doble, 1x switch de 3 pines y los 4x LEDs indicadores.

---

## 💡 Consejos de Replicación Mecánica

* **Verificación de Tolerancias:** Antes de mandar a imprimir los soportes en 3D en el **FABLAB** o **LEMUR**, verifiquen que los diámetros de las perforaciones para el switch y los tornillos de los motores coincidan exactamente con el hardware físico que adquirieron, ya que las holguras pueden variar ligeramente según el proveedor.
* **Simplificación:** Para optimizar el rendimiento de la computadora al diseñar extensiones del chasis, pueden ocultar o suprimir los hilos de los tornillos o las geometrías internas complejas de la ESP32 dentro del árbol del modelo.
