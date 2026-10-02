# Sistema de Procesamiento de Inventario y Validación de Datos (C++)

## 1. Descripción del Problema
El objetivo del proyecto es implementar un sistema por lotes en C++ capaz de procesar un inventario de productos suministrado en un archivo con formato delimitado por comas (`datos/productos.csv`). 

El programa debe operar con tolerancia a fallos: procesar secuencialmente los datos ignorando encabezados, discriminar registros íntegros de registros corruptos (valores ausentes, tipos de datos incompatibles o violaciones de dominio numérico), acumular el valor monetario global del inventario válido, permitir la consulta interactiva de un producto mediante su código en memoria y emitir un resumen auditable en `reportes/resumen.txt`.

---

## 2. Estructura del Archivo CSV (`datos/productos.csv`)
El archivo de entrada se organiza bajo una estructura tabular delimitada por comas (`,`) con la siguiente convención:

* **Línea 1 (Encabezado):** `codigo,nombre,precio,existencia` (debe omitirse programáticamente antes del ciclo de procesamiento).
* **Líneas subsiguientes (Registros de datos):** Representan artículos individuales con 4 campos posicionales:
  1. `codigo` (`std::string`): Identificador alfanumérico del producto (ej. `P001`).
  2. `nombre` (`std::string`): Descripción textual del producto (ej. `Teclado USB`).
  3. `precio` (`double`): Valor monetario unitario expresado en punto flotante (ej. `125.50`).
  4. `existencia` (`int`): Unidades físicas disponibles en bodega (ej. `8`).

---

## 3. Decisiones Técnicas y Reglas de Validación
Para asegurar que el procesamiento no aborte de manera inesperada ante datos anómalos (*runtime errors*), la validez de cada fila se evalúa de forma estricta antes de ingresar al cálculo financiero:

1. **Campos obligatorios:**
   * Las cadenas de `codigo` y `nombre` no deben ser vacías (`longitud > 0`). Filas con comas iniciales como `,Audífonos,150,7` se clasifican de inmediato como inválidas.
2. **Validación y conversión de Precio:**
   * El texto representativo se parsea hacia un tipo real (`double`) verificando que la totalidad de la cadena corresponda a dígitos numéricos válidos.
   * Regla de dominio: $\$precio > 0.0\$. Valores como `"abc"` o cantidades negativas son descartadas.
3. **Validación y conversión de Existencia:**
   * El texto representativo se parsea hacia un tipo entero (`int`).
   * Regla de dominio: $\$existencia \ge 0\$. Cantidades negativas como `-2` son descartadas; existencias en cero son aceptadas como inventario agotado válido.
4. **Manejo de flujo seguro:**
   * Las conversiones se encapsulan mediante bloques controlados para atrapar excepciones de conversión (`std::invalid_argument`, `std::out_of_range`), permitiendo que el bucle continúe procesando las filas restantes.

---

## 4. Instrucciones de Compilación y Ejecución

### Prerrequisitos
* Compilador de C++ con soporte para estándar C++11 o superior (`g++`, `clang++`).
* Estructura de carpetas requerida en el directorio de trabajo:
  ```text
  ├── main.cpp
  ├── README.md
  ├── datos/
  │   └── productos.csv
  └── reportes/
  ```

### Compilación
Ejecutar el siguiente comando en la terminal desde la raíz del proyecto:
```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o reportadora
```

### Ejecución
Asegurarse de que el directorio `reportes/` exista antes de correr el binario:
```bash
mkdir -p reportes
./reportadora
```

Al ejecutarse, el programa solicitará por consola ingresar un código para la búsqueda en memoria y generará el archivo `reportes/resumen.txt`.

---

## 5. Declaración de Uso de Inteligencia Artificial
En cumplimiento de las normas de integridad académica y transparencia técnica, se declara el uso de asistencia de IA generativa durante el desarrollo del proyecto:

* **Herramientas consultadas:** Modelo de lenguaje (KIMI K3 / Asistente de programación).
* **Consultas realizadas:**
  1. Detección y diagnóstico de deficiencias en el diseño preliminar del pseudocódigo (ausencia de ciclo de lectura persistente, pérdida del puntero de lectura al buscar códigos y manejo de tipos no numéricos en flujos de datos).
  2. Implementación de parseo robusto en C++ mediante `std::stod` y `std::stoi` verificando el índice de consumo total de caracteres para evitar fallos de segmentación con entradas alfanuméricas corruptas.
  3. Corrección del esquema de diseño (Procesos).
* **Modificaciones y adaptaciones propias:**
  * Integración de la función de validación modular con paso de parámetros por referencia.
  * Revisión, depuración en terminal y comprobación del comportamiento con los casos de prueba del enunciado.
