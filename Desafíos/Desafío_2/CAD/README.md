# Desafío 2 Mecatrónica (Modelos CAD) 📐🤖

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

* 📄 **`Ensamble Correa Transportadora Miniatura`** (Archivo de Ensamblaje Principal):
    * Este es el **Ensamblaje Completo**. Contiene la máquina entera totalmente armada. Usa este archivo para entender cómo encajan las piezas, verificar holguras o ver el gemelo digital completo.
* 📁 **`/Electronic Parts`** (Sub-carpeta):
    * Contiene los modelos CAD del hardware electrónico y electromecánico activo (ej. *Motor Paso a Paso NEMA 17*, *EasyDriver A3967*, *Arduino*, *Servos SG90*, *PCB Personalizada*). Úsalos para referencias dimensionales y tolerancias de carcasas.
* 📁 **`/Mechanic Parts`** (Sub-carpeta):
    * Contiene los modelos CAD del hardware mecánico comercial estándar (ej. *Rodamientos 627zz*, *Imanes de Neodimio*, *Pernos M3/M4*). Esencial para comprobar el espacio libre de la tornillería.
* 📁 **`/Parts`** (Sub-carpeta):
    * Contiene los **Componentes Mecánicos Personalizados Individuales** diseñados específicamente para este proyecto (ej. *Tornillo Helicoidal*, *Polea Engranaje*, *Cámara Oscura*, *Cajas*).
    * **Usa estos archivos para Impresión 3D:** Abre los componentes individuales en esta carpeta para exportarlos como `.stl` o `.3mf` para tu software de laminado (slicer).

### ⚠️ Notas Importantes de Manufactura

* **Paredes Laterales de Acrílico:** Los archivos llamados `Soportes_Acrilico` se incluyen aquí solo como referencia de ensamblaje. **NO IMPRIMIR EN 3D ESTAS PIEZAS.** Están diseñadas para Corte Láser (Acrílico 4mm).
    * 👉 **Para los archivos de producción (`.dxf`, `.beam`) y parámetros láser, por favor revisa el directorio [Acrylic Wall Manufacturing](../Acrylic%20Wall%20Manufacturing/README.md).**
* **Tolerancias:** Los modelos CAD están diseñados con tolerancias estándar para FDM. Si tu impresora no está calibrada, podrías necesitar ajustar la "Expansión Horizontal de Agujeros" en tu slicer o usar una broca para limpiar los orificios de los pernos (M3/M4).
