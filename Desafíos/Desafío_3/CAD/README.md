# Desafío 3 Mecatrónica (Modelos CAD) 📐🤖

Este directorio contiene los archivos fuente de la estructura mecánica. Ya sea que desees modificar el diseño o simplemente exportar archivos para impresión 3D, aquí encontrarás todo lo necesario.

### 📂 1. Formatos de Archivo Disponibles
Proporcionamos los modelos en dos formatos estándar de la industria para asegurar la compatibilidad con tu software CAD preferido.

| Formato | Extensión | Descripción | Uso Recomendado |
| :--- | :---: | :--- | :--- |
| **Fusion 360** | `.f3d` | **Archivos Fuente Nativos.** Contiene el historial de diseño completo y la línea de tiempo paramétrica. | Ideal para **editar**, modificar dimensiones o hacer "remix" del proyecto usando Autodesk Fusion 360. |
| **STEP** | `.step` | **Formato de Intercambio Universal.** Modelo 3D estándar sin historial de diseño. | Ideal para importar en **SolidWorks, Inventor, Rhino, Onshape** o directamente en laminadores (slicers). |

### 🗂️ 2. Estructura de Directorios

> **📍 TIP DE NAVEGACIÓN:**
> Los archivos están organizados por formato. Elige la carpeta que coincida con tu flujo de trabajo: `../Fusion360` o `../STEP`.

Dentro de cada carpeta de formato, encontrarás la siguiente jerarquía organizada:

* 📄 **`Ensamble Desafío 3 V3`** (Archivo de Ensamblaje Principal):
    * Este es el **Ensamblaje Completo**. Contiene la máquina entera totalmente armada. Usa este archivo para entender cómo encajan las piezas, verificar holguras o ver el gemelo digital completo.
* 📁 **`/Electronic Parts`** (Sub-carpeta):
    * Contiene los modelos CAD del hardware electrónico y electromecánico activo (ej. *Regulador de voltaje LM2596*, *Keypad 4x4*, *Arduino*, *Servo MG995*, *Protoboard*). Úsalos para referencias dimensionales y tolerancias de carcasas.
* 📁 **`/Mechanic Parts`** (Sub-carpeta):
    * Contiene los modelos CAD del hardware mecánico comercial estándar (ej. *Rodamientos 627zz*, *Perfiles de aluminio*, *Pernos M3/M4*). Esencial para comprobar el espacio libre de la tornillería.
* 📁 **`/Parts`** (Sub-carpeta):
    * Contiene los **Componentes Mecánicos Personalizados Individuales** diseñados específicamente para este proyecto (ej. *Soporte LCD*, *Pivote*, *Rueda*, *Minicart*).
    * **Usa estos archivos para Impresión 3D:** Abre los componentes individuales en esta carpeta para exportarlos como `.stl` o `.3mf` para tu software de laminado (slicer).
