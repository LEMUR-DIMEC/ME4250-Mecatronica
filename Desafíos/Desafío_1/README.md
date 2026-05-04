# 🏎️ Desafío 1: El Ratmóvil - Liga "Fast & Rats"
## ME4250 - Mecatrónica | Semestre 2025-2

<p align="center">
  <img src="Multimedia/Fotos/portada_ratmovil.jpg" alt="Portada Ratmóvil" width="100%">
</p>

<table align="center">
  <tr>
    <td align="center" width="50%">
      <img src="Multimedia/Fotos/galeria_1.jpg" alt="Vista Frontal" width="100%">
      <br><i>Ensamblaje del chasis y motores</i>
    </td>
    <td align="center" width="50%">
      <img src="Multimedia/Fotos/galeria_2.jpg" alt="Vista Superior" width="100%">
      <br><i>Distribución de la PCB y ESP32</i>
    </td>
  </tr>
  <tr>
    <td align="center" width="50%">
      <img src="Multimedia/Fotos/galeria_3.jpg" alt="Detalle Electrónico" width="100%">
      <br><i>Conexiones del driver TB6612FNG</i>
    </td>
    <td align="center" width="50%">
      <img src="Multimedia/Fotos/galeria_4.jpg" alt="Prueba en Pista" width="100%">
      <br><i>El Ratmóvil en la pista de pruebas</i>
    </td>
  </tr>
</table>

Este repositorio contiene la documentación y los archivos fuente correspondientes al primer desafío del curso. El objetivo principal es ensamblar, cablear y programar el "Ratmóvil", integrando tracción diferencial, control lógico y señalización visual.

---

## 📂 Estructura del Proyecto y Documentación

El proyecto está modularizado por áreas de ingeniería. Para revisar las instrucciones de montaje, el funcionamiento del código o el detalle de los circuitos, **por favor consulta el archivo `README.md` al interior de cada subcarpeta:**

* 📐 [**`CAD/`**](CAD/README.md) - Archivos de modelado 3D del chasis y los soportes del Ratmóvil.
* 💻 [**`Código/`**](Código/README.md) - Firmware en C++ desarrollado con PlatformIO y VSCode.
* 📄 [**`Documentos/`**](Documentos/README.md) - Reportes PDF, presentaciones y entregables formales.
* ⚡ [**`Electrónica/`**](Electrónica/README.md) - Diagramas esquemáticos y archivos Gerber de la PCB.
* 📷 [**`Multimedia/`**](Multimedia/README.md) - Fotos del ensamble, videos de la rutina en pista y logos del piloto.

---

## 📋 Lista de Materiales (BOM)

Para la construcción de este proyecto, se utilizaron los siguientes componentes:

* **Microcontrolador:** 1x ESP32 (NodeMCU).
* **Control de Potencia:** 1x Driver de motores TB6612FNG.
* **Actuadores:** 2x Motores DC 6V con caja reductora (Amarillos).
* **Alimentación:** 2x Baterías Ion-Litio 18650 + 1x Portapilas doble.
* **Control de Energía:** 1x Switch (interruptor) de 3 pines.
* **Apoyo Mecánico:** 1x Rueda giratoria loca (base de 4cm).
* **Señalización:** 4x LEDs (para marchas e intermitentes).
* **Integración:** 1x PCB personalizada (Desafío 1).

---

## 📊 Criterios de Evaluación
- [x] **Diagrama Esquemático:** Documentación de hardware aprobada.
- [x] **Código Comentado:** Lógica estructurada y modular.
- [x] **Funciones LED/Motores:** Señalización direccional implementada correctamente.
- [x] **Rutina de Movimiento:** Circuito completado con éxito.

---

## 👨‍💻 Créditos

* **Creadores del Desafío:** Francisco Cáceres y Valentina Abarca.
* **Colaboradores Docentes:** Fernando Navarrete, Harold Valenzuela, Fernanda Echeverría, Emilia Gutiérrez e Ignacio Núñez.

## 🎓 Acknowledgments / Agradecimientos

This project was made possible thanks to the support and facilities provided by the **University of Chile**.

*Este proyecto fue posible gracias al apoyo y las instalaciones provistas por la **Universidad de Chile**.*

| Institution / Institución | Contribution / Contribución |
| :---: | :--- |
| <img src="./Multimedia/Logos/logo_lemur.png" width="120" alt="LEMUR Logo"> | **LEMUR (Laboratorio de Ingeniería Mecatrónica y Robótica)**<br>For providing the workspace, 3D printers, and tools required for the belt assembly.<br>*(Por proveer el espacio, impresoras 3D y herramientas necesarias para el ensamblado).* |
| <img src="./Multimedia/Logos/logo_fablab.png" width="150" alt="FabLab Logo"> | **FABLAB U. de Chile**<br>For their technical advisory and access to specialized machinery, specifically the Beambox Series Pro laser cutter.<br>*(Por su asesoría y el uso de máquinas especializadas, principalmente la cortadora láser Beambox Series Pro).* |

---
*Open Source Project - ME4250 Mecatrónica - 2025*
