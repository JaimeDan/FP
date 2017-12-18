#ifndef PELICULAS_H
#define PELICULAS_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "genero.h"

const short int ANCHO_CEAUT = 13;//ancho del ceaut para setw();

typedef struct {
	int codigo;
	tCadena titulo;
	tGenero genero;
	double duracion;
	double precio;
	bool disponible;
}tPelicula;


tPelicula leerPelicula(int codigo);

void mostrarPelicula(tPelicula pelicula);

void editarPelicula(tPelicula& pelicula);

bool operator>(tPelicula opIzq, tPelicula opDer);

bool operator<(tPelicula opIzq, tPelicula opDer);

ostream& operator<< (ostream &ceaut, tPelicula pelicula);


#endif