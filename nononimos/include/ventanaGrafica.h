/**
 * @file ventanaGrafica.h
 * Librería de funciones para gestionar una ventana/lienzo en el que pintar elementos básicos.
 */
#ifndef VENTANAGRAFICA_H
#define VENTANAGRAFICA_H

/**
 * Constante PI.
 */
const double PI= 3.14159265;

/**
 * Constante RPG. Radianes por Grado (RPG= PI/180.0).
 */
const double RPG= 0.01745329;

/**
 * Constante VGNUMCOLS. Número de colores de la librería.
 */
const int VGNUMCOLS= 5;

/**
 * Tipo VGColores: enumerado de los colores disponibles en la librería.
 */
typedef enum {VGBlanco, VGRojo, VGVerde, VGAzul, VGNegro} VGColores;

/**
 * Constante VGXLEFT. Extremo izquierdo del eje X del sistema de coordenadas de la ventana gráfica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGXLEFT= -50;

/**
 * Constante VGXRIGHT. Extremo derecho del eje X del sistema de coordenadas de la ventana gráfica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGXRIGHT= 50;

/**
 * Constante VGYTOP. Extremo superior del eje Y del sistema de coordenadas de la ventana gráfica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGYTOP=  50;

/**
 * Constante VGYBOT. Extremo inferior del eje Y del sistema de coordenadas de la ventana gráfica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGYBOT= -50;

/**
 * Inicialización de la ventana gráfica. El comportamiento es:
 * <ul>
 *   <li>vgInit(true) ventana en blanco con los ejes del sistema de coordenadas.</li>
 *   <li>vgInit(false) ventana en blanco. </li>
 * </ul>
 * @param mostrarEjes Mostrar los ejes del sistema de coordenadas.
 */
bool vgInit(bool mostrarEjes);

/**
 * Desactiva la ventana gráfica.
 */
void vgEnd(); 

/**
 * Limpia/Elimina el contenido actual de la ventana gráfica.
 */
void vgClear();

/**
 * Pinta un segmento entre los puntos (x1, y1) e (x2, y2)
 *
 * @param x1 Coordenada x del punto inicial.
 * @param y1 Coordenada y del punto inicial.
 * @param x2 Coordenada x del punto destino.
 * @param y2 Coordenada y del punto destino.
 */
void vgLine( double x1, double y1, double x2, double y2);

/**
 * Pinta un punto en coordenadas (x, y)
 *
 * @param x Coordenada x del punto.
 * @param y Coordenada y del punto.
 */
void vgPoint(double x, double y);

/**
 * Constante VGDA. Dimensión de los arrays de puntos.
 */
const int VGDA= 200; 

/**
 * Pinta un array de puntos.
 *
 * @param puntos Array de pares de coordenadas (x, y) a pintar (máximo VGDA/2 puntos).
 * @param numPuntos Número de puntos a pintar.
 */
void vgPoints(double puntos[VGDA], int numPuntos);

/**
 * Pinta una secuencia de segmentos dados en un array de puntos.
 *
 * @param puntos Array de pares de puntos que definen la lista de segmentos [<(x0, y0), (x1, y1)>, ...].
 * @param numPuntos Número de segmentos a pintar.
 */
void vgLines(double puntos[VGDA], int numPuntos);

/**
 * Constante VGDM. Dimensión de la matriz de motivos (matriz cuadrada de colores).
 */
const int VGDM= 10; 

/**
 * Pinta un motivo dado por una matriz de VGDM x VGDM colores. 
 * Esta función se encarga de pintar los puntos (x + c, y + f) del color mat[f][c].
 *
 * @param x Coordenada del eje x de la esquina superior izquierda de la posición en la que el motivo será pintado.
 * @param y Coordenada del eje y de la esquina superior izquierda de la posición en la que el motivo será pintado.
 * @param motivo Matriz de VGDM x VGDM colores que representa el motivo a pintar.
 */
void vgMatriz(double x, double y, VGColores motivo[VGDM][VGDM]);

/**
 * Pinta un motivo dado por un array de puntos.
 *
 * @param x Coordenada del eje x del punto utilizado como origen.
 * @param y Coordenada del eje y del punto utilizado como origen.
 * @param puntos Array de pares de coordenadas (x, y) a pintar (máximo VGDA/2 puntos).
 * @param numPuntos Número de puntos a pintar.
 */
void vgPoints(double x, double y, double puntos[VGDA],  int numPuntos);

/**
 * Pinta un motivo dado por una secuencia de segmentos.
 *
 * @param x Coordenada del eje x del punto utilizado como origen.
 * @param y Coordenada del eje y del punto utilizado como origen.
 * @param puntos Array de pares de puntos que definen la lista de segmentos [<(x0, y0), (x1, y1)>, ...].
 * @param numPuntos Número de segmentos.
 */
void vgLines( double x, double y, double puntos[VGDA], int numPuntos);

/**
 * Pinta una cadena de caracteres.
 *
 * @param x Coordenada del eje x donde se pintará el primer carácter de la cadena.
 * @param y Coordenada del eje y donde se pintará el primer carácter de la cadena.
 * @param cad Cadena a pintar.
 */
void vgCString(double x, double y, const char cad[]);

/**
 * Establece el color utilizado para pintar los elementos gráficos.
 *
 * @param col Color utilizado para pintar los elementos gráficos.
 */
void vgColor(VGColores col);


/**
 * Inicializa la ventana gráfica.
 * 
 * @param argc Número de argumentos pasados a la aplicación.
 * @param argv Array de parámetros pasados a la aplicación.
 */
bool vgInit(int argc, char *argv[]);

#endif