#ifndef GENERO_H
#define GENERO_H

typedef enum tGenero {ciencia_ficcion, fantasia, comedia, terror, drama, comedia_romantica};

int menuGenero();

tGenero leerGenero();

void escribirGenero(tGenero genero);

void limpiar();

ostream& operator<< (ostream &ceaut, tGenero genero);




#endif