#ifndef PELICULAS_H
#define PELICULAS_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//#include "peliculas.h"
//#include "listapelis.h"
#include "genero.h"

typedef struct {
	int codigo;
	string titulo;
	tGenero genero;
	double duracion;
	double precio;
	bool disponible;
}tPelicula;

tPelicula leerPelicula();

void mostrarPelicula(tPelicula pelicula);

void editarPelicula(tPelicula& pelicula);

bool operator>(tPelicula opIzq, tPelicula opDer);

bool operator<(tPelicula opIzq, tPelicula opDer);

ostream& operator<< (ostream &ceaut, tPelicula pelicula);


#endif