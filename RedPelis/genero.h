#ifndef GENERO_H
#define GENERO_H
#include "funciones.h"

typedef enum tGenero {Ciencia_ficcion, Fantasia, Comedia, Terror, Drama, Comedia_romantica};

int menuGenero(bool get_option);

tGenero leerGenero();

tGenero leerGenero(int n);

tGenero generoDeArchivo(ifstream& flujo);

void escribirGenero(tGenero genero);

ostream& operator<< (ostream &ceaut, tGenero genero);




#endif