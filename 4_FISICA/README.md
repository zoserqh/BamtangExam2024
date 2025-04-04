# Problema4: FISICA
Cree un simulador para disparar pelotas circulares. Considerar por simplicidad un cuarto rectangular cerrado y de gravedad **G**. Las pelotas son círculos que deben de chocar contra las paredes y entre ellas, luego de un tiempo de estar inmóviles deben desaparecer. 

Para este problema considere coeficientes de fricción y elasticidad convenientes y demás suposiciones que cree necesarias y comentarlas en su código. Su programa debe permitir mover el origen de disparo **O** y la velocidad y angulo inicial de disparo **V**. Las pelotas deben ser lanzadas al apretar la tecla de espacio. **No usar librerías físicas existentes**, pero puedes usar cualquier librería de gráficos **realtime** existente, como SDL2, SFML, OpenGL, etc.

Implementar la función: **shootBall()**
## Build
Para generar el ejecutable, ubicarse a la altura del archivo Makefile y ejecutar el comando make

    make
Para ejecutar, ubicarse dentro de la carpeta exec

    ./run

## Resultados
<!--- (![Alt text](dataReadme/playing.png "playing")
[video here](https://youtu.be/G9W5ZZFAmH4)
--->
## Notes
<!--- Este proyecto se realizó con openGL moderno(4.6 core-profile) usando shaders.
Para el manejo de periféricos y ventanas se uso [GLFW](https://www.glfw.org/) adicionalmente [glad](https://glad.dav1d.de/).
Para el uso de vectores y matrices homogeneas se usó [glm](https://glm.g-truc.net/0.9.8/index.html).

Renderizado: 

No se usó texturas, el laberinto, el círculo y las letras A y B son completamente generadas a partir de un array de posiciones y colores.

El renderizado del laberinto se hizo a partir de 5 tipos de piezas que con transformaciones de escalamiento, rotación y traslación forman el laberinto.

Como el laberinto y las letras A(start) y B(final) no cambian durante cada renderizado se optó por renderizarse fuera de pantalla guardandolo en un frame buffer object y usandolo como textura cuando se renderiza en pantalla. Esto elimina el trabajo repetitivo de construir el laberinto y las letras A y B cada vez que se renderice. Una vez obtenida esta información como textura se borran los VBO VAO del laberinto y de las letras. liberando asi espacio en la memoria de la GPU.
    --->