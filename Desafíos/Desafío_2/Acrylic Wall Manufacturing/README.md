# Desafío 2 Mecatrónica - Manufactura Pared de Acrílico🔦⚙️


Esta carpeta contiene los archivos de fabricación para las **Paredes Estructurales Laterales** de la cinta transportadora.

Estos componentes son críticos para alojar los rodamientos. Utilizamos **Corte Láser** en **Acrílico Transparente de 4mm**.

### 📋 1. Especificaciones de la Pieza

| Especificación | Valor | Notas |
| --- | --- | --- |
| **Material** | Acrílico Transparente | Espesor de 4mm es crítico. |
| **Dimensiones Plancha** | **400mm x 300mm** | Tamaño de stock comercial. |
| **Dimensión Pieza** | 390mm x 100mm | *⚠️ OJO: Margen muy justo a lo largo (5mm por lado).* |
| **Rendimiento** | **3 Unidades por Plancha** | *Requiere alineación de "Cero" perfecta (Ver abajo).* |

### 📂 2. Archivos Incluidos

* **`Soporte_Acr_lico.beam`**: **(Recomendado)** Archivo nativo de Beam Studio. Contiene las capas preconfiguradas para grabado y corte. Listo para cargar en cortadoras Flux.
* **`Soporte_Acr_lico.dxf`**: Archivo vectorial estándar. Úsalo si necesitas importar la geometría a otro software CAM (LightBurn, RDWorks) o modificar el CAD.
* **`Plano Fabricación paredes de acrílico V1.pdf`**: Plano técnico con cotas y tolerancias para control de calidad.

### 🖨️ 3. Flujo de Trabajo (Beambox Pro 50W)

El objetivo es encajar **3 piezas verticalmente** (3 x 100mm) en una plancha de **300mm de alto**. Dado que el **margen vertical es cero**, la calibración es obligatoria.

**⚠️ PREPARACIÓN:**

1. **Retirar el film protector** de la plancha de acrílico **ANTES** de meterla a la máquina.
2. Limpiar la plancha si es necesario.

#### **Fase 1: Calibración ("La Línea de Cero")** 📏

*Antes del trabajo completo, debes definir el borde superior exacto del material.*

1. Coloca la plancha en la cama de la cortadora.
2. En Beam Studio, dibuja una línea horizontal simple en la parte superior del lienzo ().
3. **Graba esta línea** sobre la plancha.
4. Verifica el resultado: Esta línea te indica dónde interpreta el láser el "Inicio". Ajusta la posición física de la plancha hasta que esta línea coincida exactamente con el borde superior del material.

#### **Fase 2: El Trabajo** ⚙️

Carga el archivo `Soporte_Acr_lico.beam` y verifica los parámetros (calibrados para Beambox Pro 50W):

* **Capa 1: Grabado (Logos/Texto)**
* *Método:* Grabado Raster (Shading).
* *Potencia:* 15% - 20% | *Velocidad:* 250 - 300 mm/s


* **Capa 2: Corte**
* *Método:* Corte Vectorial.
* *Potencia:* 55% - 60% | *Velocidad:* 5 - 7 mm/s
* *Pases:* 1



### 🛠️ 4. Post-Procesado y Limpieza

* **Limpieza:** Lavar las piezas utilizando **solamente agua / alcohol isopropílico y una esponja suave**.
* *⛔ NO usar paños abrasivos (el acrílico se raya fácil).*



### ♻️ 5. Eco-Tip: Reutilización de Sobrantes

¡No desperdicies material! El proceso de corte genera sobrantes internos de alta calidad que se acumulan tras varias planchas:

* **Rectángulo Redondeado Interno:** Tiene el tamaño ideal para fabricar **Placas de Nombre para escritorio** o señalética de oficina.
* **Discos (Ø22mm y Ø20mm):** Los recortes provenientes de los agujeros para rodamientos y el botón de encendido pueden reutilizarse como fichas, llaveros o espaciadores.

Nota: Estas piezas deben estar guardadas en una bolsa de papel.
