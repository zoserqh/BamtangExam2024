# Problem 2:    Laberinto
Crear un generador de laberintos aleatorios de dos dimensiones de tamaño 'n' (n: impar > 3). El punto inicial **A** siempre se encontrará en la esquina superior izquierda. El punto final **B** deberá encontrarse al final de la ruta **más larga** dentro de tu laberinto generado (que no necesariamente será la esquina superior derecha). El laberinto solo debe tener caminos horizontales y verticales, no diagonales.

Ademas para ir de **A** a **B** deberá existir **solo un camino posible**. 

Ejemplo:

n = 11 (* = muro, A = inicio, B = fin)

    ***********

    *A  *    B*

    *** * *****

    * * * *   *

    * * * * * *

    *   *   * *

    * *** *** *

    *   * *   *

    *** *** * *

    *       * *

    ***********

Implementar la función: **createMaze2D**( n ) 

No generar cualquier laberinto, recuerda que se pide un laberinto de un solo camino posible entre A y B.
No se considerán soluciones que generen laberintos con múltiples caminos entre A y B.

## Build
Para generar el ejecutable, ubicarse a la altura del archivo Makefile y ejecutar el comando make

    make
Para ejecutar, ubicarse dentro de la carpeta exec

    ./run
En caso no tenga instalado openCV, se sugiere comentar las lineas donde openCV sea usado y tambien comentar el método displayMazeByWindow().

## Resultados
Generación de un laberinto de dimension 5x5:

![Alt text](data/mazeWindow5.png "mazeWindow5" )
![Alt text](data/mazeTerminal5.png "mazeTerminal5")

Generación de un laberinto de dimension 15x15:

![Alt text](data/mazeWindow15.png "mazeWindow15")
![Alt text](data/mazeTerminal15.png "mazeTerminal15")

Generación de un laberinto de dimension 45x45:

![Alt text](data/mazeWindow45.png "mazeWindow45")
![Alt text](data/mazeTerminal45.png "mazeTerminal45")

