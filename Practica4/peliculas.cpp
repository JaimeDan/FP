//#include <iostream>
//using namespace std;
#include "peliculas.h"

//#include "listapelis.h"



/*void editarPelicula(tListaPelis/*& lista){
	int posicion, codigo;
	tPelicula pelicula;
	cout << "Introduzca el codigo de una pelicula: ";
	cin >> codigo;
	buscarPelicula(lista, codigo, posicion);


}*/

tPelicula leerPelicula(){
	tPelicula pelicula;
	
	do{
		cout << "Introduzca el codigo de la pelicula: ";
		limpiar();
		cin >> pelicula.codigo;		
	}while (cin.fail());
	
	do{
		cout << "Introduzca el titulo de la pelicula: ";
		limpiar();
		cin >> pelicula.titulo;
	}while (cin.fail());
	do{
		cout << "Introduzca el genero de la pelicula: ";
		limpiar();
		pelicula.genero = leerGenero();
	}while (cin.fail());
	do{
		cout << "Introduzca la duracion de la pelicula: ";
		limpiar();
		cin >> pelicula.duracion;
	}while (cin.fail());
		do{
		cout << "Introduzca el precio de la pelicula: ";
		limpiar();
		cin >> pelicula.precio;
	}while (cin.fail());

	pelicula.disponible = true; 
	return pelicula;
}

void mostrarPelicula (tPelicula pelicula){
	cout << "Hello, world";
}

bool operator>(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo > opDer.codigo;
}

bool operator<(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo < opDer.codigo;
}

ostream& operator<< (ostream &ceaut, tPelicula pelicula){
	ceaut << setw(12) << left << "Codigo:\t\t"  << left << pelicula.codigo << endl;
	ceaut << setw(12) << left << "Titulo:\t\t" << left << pelicula.titulo << endl;
	ceaut << setw(12) << left << "Genero:\t\t"  << left << pelicula.genero << endl;
	ceaut << setw(12) << left << "Duracion:\t "<< left << pelicula.duracion << " horas." << endl;
	ceaut << setw(12) << left << "Disponible?:\t   ";// << setw(12) << right << pelicula.disponible ? "SI": "NO";ceaut << endl;
	pelicula.disponible ? ceaut << left << "SI": ceaut << left << "NO"; ceaut << endl;
	return ceaut;
}