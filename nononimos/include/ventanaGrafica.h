/**
 * @file ventanaGrafica.h
 * Librer�a de funciones para gestionar una ventana/lienzo en el que pintar elementos b�sicos.
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
 * Constante VGNUMCOLS. N�mero de colores de la librer�a.
 */
const int VGNUMCOLS= 5;

/**
 * Tipo VGColores: enumerado de los colores disponibles en la librer�a.
 */
typedef enum {VGBlanco, VGRojo, VGVerde, VGAzul, VGNegro} VGColores;

/**
 * Constante VGXLEFT. Extremo izquierdo del eje X del sistema de coordenadas de la ventana gr�fica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGXLEFT= -50;

/**
 * Constante VGXRIGHT. Extremo derecho del eje X del sistema de coordenadas de la ventana gr�fica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGXRIGHT= 50;

/**
 * Constante VGYTOP. Extremo superior del eje Y del sistema de coordenadas de la ventana gr�fica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGYTOP=  50;

/**
 * Constante VGYBOT. Extremo inferior del eje Y del sistema de coordenadas de la ventana gr�fica ([VGXLEFT, VGXRIGHT]x[VGYBOT, VGYTOP]).
 */
const int VGYBOT= -50;

/**
 * Inicializaci�n de la ventana gr�fica. El comportamiento es:
 * <ul>
 *   <li>vgInit(true) ventana en blanco con los ejes del sistema de coordenadas.</li>
 *   <li>vgInit(false) ventana en blanco. </li>
 * </ul>
 * @param mostrarEjes Mostrar los ejes del sistema de coordenadas.
 */
bool vgInit(bool mostrarEjes);

/**
 * Desactiva la ventana gr�fica.
 */
void vgEnd(); 

/**
 * Limpia/Elimina el contenido actual de la ventana gr�fica.
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
 * Constante VGDA. Dimensi�n de los arrays de puntos.
 */
const int VGDA= 200; 

/**
 * Pinta un array de puntos.
 *
 * @param puntos Array de pares de coordenadas (x, y) a pintar (m�ximo VGDA/2 puntos).
 * @param numPuntos N�mero de puntos a pintar.
 */
void vgPoints(double puntos[VGDA], int numPuntos);

/**
 * Pinta una secuencia de segmentos dados en un array de puntos.
 *
 * @param puntos Array de pares de puntos que definen la lista de segmentos [<(x0, y0), (x1, y1)>, ...].
 * @param numPuntos N�mero de segmentos a pintar.
 */
void vgLines(double puntos[VGDA], int numPuntos);

/**
 * Constante VGDM. Dimensi�n de la matriz de motivos (matriz cuadrada de colores).
 */
const int VGDM= 10; 

/**
 * Pinta un motivo dado por una matriz de VGDM x VGDM colores. 
 * Esta funci�n se encarga de pintar los puntos (x + c, y + f) del color mat[f][c].
 *
 * @param x Coordenada del eje x de la esquina superior izquierda de la posici�n en la que el motivo ser� pintado.
 * @param y Coordenada del eje y de la esquina superior izquierda de la posici�n en la que el motivo ser� pintado.
 * @param motivo Matriz de VGDM x VGDM colores que representa el motivo a pintar.
 */
void vgMatriz(double x, double y, VGColores motivo[VGDM][VGDM]);

/**
 * Pinta un motivo dado por un array de puntos.
 *
 * @param x Coordenada del eje x del punto utilizado como origen.
 * @param y Coordenada del eje y del punto utilizado como origen.
 * @param puntos Array de pares de coordenadas (x, y) a pintar (m�ximo VGDA/2 puntos).
 * @param numPuntos N�mero de puntos a pintar.
 */
void vgPoints(double x, double y, double puntos[VGDA],  int numPuntos);

/**
 * Pinta un motivo dado por una secuencia de segmentos.
 *
 * @param x Coordenada del eje x del punto utilizado como origen.
 * @param y Coordenada del eje y del punto utilizado como origen.
 * @param puntos Array de pares de puntos que definen la lista de segmentos [<(x0, y0), (x1, y1)>, ...].
 * @param numPuntos N�mero de segmentos.
 */
void vgLines( double x, double y, double puntos[VGDA], int numPuntos);

/**
 * Pinta una cadena de caracteres.
 *
 * @param x Coordenada del eje x donde se pintar� el primer car�cter de la cadena.
 * @param y Coordenada del eje y donde se pintar� el primer car�cter de la cadena.
 * @param cad Cadena a pintar.
 */
void vgCString(double x, double y, const char cad[]);

/**
 * Establece el color utilizado para pintar los elementos gr�ficos.
 *
 * @param col Color utilizado para pintar los elementos gr�ficos.
 */
void vgColor(VGColores col);


/**
 * Inicializa la ventana gr�fica.
 * 
 * @param argc N�mero de argumentos pasados a la aplicaci�n.
 * @param argv Array de par�metros pasados a la aplicaci�n.
 */
bool vgInit(int argc, char *argv[]);

#endif