#include <iostream>
using namespace std;
#include "peliculas.h"

#include "listapelis.h"
#include "funciones.h"

tPelicula leerPelicula(int codigo){
	tPelicula pelicula;
	pelicula.codigo = codigo;
	cout << "Introduzca el titulo de la pelicula: ";
	getChars(pelicula.titulo);
	pelicula.genero = leerGenero();
	cout << "Introduzca la duracion de la pelicula: ";
	pelicula.duracion = getDouble();
	cout << "Introduzca el precio de la pelicula: ";
	pelicula.precio = getDouble();
	pelicula.disponible = true; 
	return pelicula;
}

void editarPelicula(tPelicula& pelicula){
	char c;
	bool error = true;
	int genero;
	cout << "Introduzca el titulo de la pelicula: ";
	c = cin.peek();
	if (c!='\n') getChars(pelicula.titulo);
	else cin.get(c);
	while (error){
		limpiar();
		menuGenero(false);
		c = cin.peek();
		if (c == '\n'){ cin.get(c); error = false;}
		else if (!isdigit(c) || c < '0' || c  > '9') cout << "Valor no valido, introduzcalo de nuevo: ";
		else {
			cin >> genero;
			pelicula.genero = leerGenero(genero);
			error = false;
		}
	}limpiar();
	cout << "Introduzca la duracion de la pelicula: ";
	c = cin.peek();
	if (c!='\n') pelicula.duracion = getDouble();
	else cin.get(c);
	cout << "Introduzca el precio de la pelicula: ";
	c = cin.peek();
	if (c!='\n') pelicula.precio = getDouble();
	else cin.get(c);
	
	
}

bool operator>(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo > opDer.codigo;
}

bool operator<(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo < opDer.codigo;
}

ostream& operator<< (ostream &ceaut, tPelicula pelicula){
	ceaut << setfill(' ') << setw(ANCHO_CEAUT) << right << "Codigo:\t"  << left << pelicula.codigo << endl;
	ceaut << setw(ANCHO_CEAUT) << right << "Titulo:\t" << left << pelicula.titulo << endl;
	ceaut << setw(ANCHO_CEAUT) << right << "Genero:\t"  << left << pelicula.genero << endl;
	ceaut << setw(ANCHO_CEAUT) << right << "Duracion:\t"<< left << pelicula.duracion << " minutos" << endl;
	ceaut << setw(ANCHO_CEAUT) << right << "Precio:\t"<< left << pelicula.precio << " euros" << endl;	
	ceaut << setw(ANCHO_CEAUT) << right << "Disponible?:\t";
	pelicula.disponible ? ceaut << "SI": ceaut << left << "NO";
	ceaut << endl;;
	return ceaut;
}