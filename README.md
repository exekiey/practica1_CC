# Práctica 1 - Complejidad Computacional

Este proyecto implementa un simulador de autómatas de pila (PDA, Pushdown Automata) en C++ para reconocer cadenas de entrada según una definición textual del autómata.

El programa lee la especificación del autómata desde un archivo de texto, procesa una o varias cadenas desde otro archivo y determina si cada una es aceptada o rechazada.

## Objetivo

La práctica está enfocada en modelar y validar un autómata de pila que reconoce un lenguaje concreto mediante un recorrido por estados y pila, usando transiciones con lectura de entrada y expansión de la pila.

El ejemplo incluido reconoce un lenguaje del tipo palíndromo con longitud par, definido en el archivo `automata.txt`:

- `L = {ww^R}`
- En la práctica, el ejemplo reconoce palabras palíndromas de longitud par.

## Funcionalidades

- Lectura de un autómata desde un archivo de texto.
- Soporte de transiciones con símbolo de entrada y símbolo de cima de pila.
- Soporte de transiciones epsilon representadas con `.`.
- Simulación de la pila durante la ejecución.
- Modo de traza opcional para ver la evolución del autómata.
- Validación de múltiples cadenas desde un archivo de entrada.

## Estructura del proyecto

- `main.cpp`: punto de entrada del programa.
- `include/`: encabezados (`.h`) del proyecto.
- `reader.cpp`: lectura del autómata y del archivo de entrada.
- `automaton.cpp`: definición del autómata.
- `solver.cpp`: lógica de resolución del problema.
- `state.cpp`: representación de estados.
- `symbol.cpp`: representación de símbolos.
- `transition.cpp`: definición de transiciones.
- `node.cpp`: nodos del recorrido BFS.
- `tools.cpp`: utilidades auxiliares.
- `automata.txt`: ejemplo de autómata.
- `input.txt`: ejemplo de cadenas de entrada.
- `Makefile`: compilación del proyecto; guarda los archivos objeto en `build/`.

## Formato del archivo del autómata

El archivo del autómata sigue este esquema:

```text
Q
Σ
Γ
q0
A0
F
transición_1
transición_2
...
```

Donde:

- `Q`: conjunto de estados.
- `Σ`: alfabeto de entrada.
- `Γ`: alfabeto de la pila.
- `q0`: estado inicial.
- `A0`: símbolo inicial de la pila.
- `F`: estados finales.
- Cada transición tiene el formato:

```text
estado_actual símbolo_entrada cima_pila estado_destino simbolos_a_apilar
```

Ejemplo real del proyecto:

```text
p q r
0 1
0 1 S
p
S
r
p 0 S p 0S
p 1 S p 1S
p 0 0 p 00
p 0 1 p 01
p 1 0 p 10
p 1 1 p 11
p . S q S
p . 0 q 0
p . 1 q 1
q 0 0 q .
q 1 1 q .
q . S r S
```

- `.` representa epsilon.
- El contenido de `simbolos_a_apilar` puede ser vacío, un símbolo o varios símbolos.

## Formato del archivo de entrada

El archivo de entrada contiene una cadena por línea. Cada símbolo debe pertenecer al alfabeto de entrada del autómata.

Ejemplo:

```text
0110
001100
```

## Compilación

Desde la raíz del proyecto ejecuta:

```bash
make
```

Esto genera el ejecutable `main`.

## Ejecución
El programa recibe los siguientes argumentos por línea de comandos:
-config <f> :fichero de texto con la configuración del autómata.
-trace <y|n> :activa (y) o desactiva (n) la traza durante la ejecución.
-in <f> :fichero de texto con las cadenas de entrada que se comprobarán.
```bash

Los tres argumentos son obligatorios.

Ejemplo de ejecución con traza:

./main -config automata.txt -trace y -in input.txt

Ejemplo de ejecución sin traza:

./main -config automata.txt -trace n -in input.txt
```

- `trace`: usa `y` para activar la traza, o `n` para ejecutarlo sin mostrar el recorrido detallado.

Ejemplo:

```bash
./main automata.txt y input.txt
```

## Salida esperada

El programa imprime si cada cadena es aceptada o rechazada. Ejemplo:

```text
Cadena: 0110 -> Aceptada
Cadena: 001100 -> Rechazada
```

Si se activa la traza (`y`), además se muestran los estados, la entrada restante, el contenido de la pila y las transiciones posibles en cada paso.

## Requisitos

- Compilador de C++ con soporte para C++17.
- `make`.

## Autoría

Proyecto desarrollado para la práctica de complejidad computacional / teoría de autómatas.
