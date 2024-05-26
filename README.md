# Resolución de puzzle 8 : Grafo implícito

![Imagen problema](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/5ac62eac-b5f9-44b5-a298-6eebc2ce583d)

## Descripción:
Este programa permite, a través de un estado inicial de un puzzle 8, encontrar sus solución utilizando los mecanismos de búsqueda asociados a la estructura del grafo.

## Sobre el puzzle 8:

1. **Configuración inicial**: El puzzle comienza con los bloques en una disposición aleatoria o predefinida que no sigue el orden secuencial.
   
2. Movimientos permitidos: Puedes deslizar un bloque adyacente a la casilla vacía hacia esta, efectivamente moviendo la casilla vacía a la posición del bloque y dejando la posición anterior del bloque ahora vacía.
 
3. Objetivo: El objetivo final es organizar los bloques de manera que los números estén ordenados del 1 al 8, empezando por la casilla superior central y siguiendo de izquierda a derecha y de arriba a abajo. La casilla en la esquina superior izquierda debe quedar vacía.

## Instalación, compilación y ejecución:
### Por GitHub:
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomiendo usar Repl.it para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
1. Ingresa a [Replit](https://repl.it/)
2. Inicia sesión, o crea una cuenta si es que no tienes.
3. Una vez en tu página principal, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: [Tarea 3 - Puzzle 8](https://replit.com/@IgnaciaLBrahim/tarea-3-puzzle-8)
5. Replit clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar el código.
7. ¡Todo listo!

### Por Replit:
Si no deseas clonar el repositorio;
1. Inicia sesión a tu cuenta de Replit, o crea una cuenta si no la tienes.
2. Luego ingresa a [Tarea 3 - Puzzle 8](https://replit.com/@IgnaciaLBrahim/tarea-3-puzzle-8).
3. Selecciona la opción "Fork".
4. Esto creará una copia del proyecto en tu cuenta, por lo que podrás correrla y editarla si deseas, sin modificar el proyecto original.
5. Puedes compilar y correr el proyecto con "Run".

## Funcionalidades

### Funcionando correctamente:
En el programa podrás encontrar un menú con las siguientes funcionalidades:  

`1) Búsqueda en Profundidad: ` Realiza una búsqueda en profundidad para encontrar la solución al puzzle 8. Explora todos los caminos posibles desde el estado inicial, profundizando en sus ramas de movimientos antes de retroceder, hasta encontrar el estado final que resuelve el puzzle o alcanzar una profundidad máxima de 15 movimientos. En ese último caso, se pasa a la siguiente rama).

`2) Buscar en Anchura: `  Realiza una búsqueda en anchura para encontrar la solución al puzzle 8. Para eso, explora todos los caminos posibles desde el estado inicial, nivel por nivel; primero revisa todos los estados alcanzables en un solo movimiento, (1, 2, 3, 4), luego todos los estados alcanzables en os movimientos (se comienzan a combinar), y así sucesivamente, hasta encontrar el estado final que resuelve el puzzle.

`3) Buscar Mejor Primero: ` La función "Mejor Primero" debería explorar los posibles movimientos en función de la distancia de cada pieza desde su posición actual hasta su posición objetivo. Selecciona el movimiento que tiene menor distancia en cada paso, lo que tiende a dirigir la búsqueda hacia la solución óptima del puzzle 8. (Funcionalidad no disponible)

`4) Salir: ` Se da la opción de del programa. Los archivos cargados deberán cargarse de nuevo si es que se vuelve a utilizar.

### Problemas conocidos:

El mayor problema tiene relación con la limitación del radio de búsqueda DFS en torno a la cantidad de acciones hechas a partir del estado inicial. No limitar las acciones que dan lugar a las ramas entre 13 y 15 hace que el programa se caiga.

### A mejorar:

1) Mejorar el rendimiento en cuanto a iteraciones de las búsquedas. 
2) Implementar una interfaz de usuario más amigable en general.
3) Implementar la función "Buscar Mejor Primero"
   
## Ejemplo de uso e interacción:
Para poder interactuar con el programa, deberás apretar el botón "Run" y luego ir al apartado "Console" para poder interactuar con el menú:

![Captura de pantalla 2024-05-25 202308](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/7b46f35d-15ff-4fae-a657-086b36099745)

*Vista a la interfaz*.


`1) Búsqueda en Profundidad: `

Se muestra el estado inicial del puzzle cargado y se pueden apreciar los pasos que se siguen para llegar a la solución a través de la búsqueda en profundidad:

![Captura de pantalla 2024-05-25 203117](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/ad547e13-2468-44b5-acaf-ddfbf91eec74)

También se puede visualizar cuantas iteraciones hizo la búsqueda para llegar a la solución:

![Captura de pantalla 2024-05-25 203134](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/e153cc23-ea79-4ce5-8886-76707d777cf7)


`2) Buscar en Anchura: `

Se muestra el estado inicial del puzzle cargado y se pueden apreciar los pasos que se siguen para llegar a la solución a través de la búsqueda en profundidad:

![Captura de pantalla 2024-05-25 203335](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/48a36e45-839b-49d7-a275-7626f2378541)

También se puede visualizar cuantas iteraciones hizo la búsqueda para llegar a la solución:

![Captura de pantalla 2024-05-25 203353](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/33ef7b22-921b-4769-b9b1-fd094899c6bd)


`3) Buscar Mejor Primero: `

Se muestra el aviso de que aún no se implementa esta funcionalidad del programa:

![Captura de pantalla 2024-05-25 203421](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/83f3ab47-475b-490d-a6f4-a1e51ec751fb)


`4) Salir: `

Si se sale del programa, se tendrán que cargar de nuevo los datos del archivo puzzle.txt, que contiene el puzzle a resolver.


![Captura de pantalla 2024-05-25 203437](https://github.com/IgnaciaBrahim/tarea-3-puzzle8/assets/137849174/5a2df475-ad4f-4817-99d5-8311f3846c19)
