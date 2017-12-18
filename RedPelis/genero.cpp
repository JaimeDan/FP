#include <iostream>
using namespace std;

#include "genero.h"



int menuGenero(bool get_option){
	char c;
	int opcion;
	cout << "Seleccione el genero de la pelicula de entre los siguientes:\n";
	cout << "1.- Ciencia-ficcion\n";
    cout << "2.- Fantasia\n";
    cout << "3.- Comedia\n";
    cout << "4.- Terror\n";
    cout << "5.- Drama\n";
    cout << "6.- Comedia-romantica\n";
    cout << "Opcion: ";
    if (get_option){
		c = cin.peek();
		if (!isdigit(c)) opcion = 0;
		else cin >> opcion;
		return opcion;
	}
    
}
tGenero leerGenero(){
	tGenero genero;
	int opcion_gen = 0;
	while (opcion_gen == 0){
        limpiar();
        opcion_gen = menuGenero(true);
		limpiar();
		if		(opcion_gen == 1) genero = Ciencia_ficcion;
		else if (opcion_gen == 2) genero = Fantasia;
		else if (opcion_gen == 3) genero = Comedia;
		else if (opcion_gen == 4) genero = Terror;
		else if (opcion_gen == 5) genero = Drama;
		else if (opcion_gen == 6) genero = Comedia_romantica;
		else{
			cout << "Opcion no valida!\n";
			opcion_gen = 0;
		}
    }
	return genero;	
}

tGenero leerGenero(int n){
	tGenero genero;
	
		if		(n == 1) genero = Ciencia_ficcion;
		else if (n == 2) genero = Fantasia;
		else if (n == 3) genero = Comedia;
		else if (n == 4) genero = Terror;
		else if (n == 5) genero = Drama;
		else if (n == 6) genero = Comedia_romantica;
		else genero = Ciencia_ficcion;

	return genero;	
}

tGenero generoDeArchivo(ifstream& flujo){
	tGenero genero = Ciencia_ficcion;
	int num;
	flujo >> num;
	if		(num == 0) genero = Ciencia_ficcion;
	else if (num == 1) genero = Fantasia;
	else if (num == 2) genero = Comedia;
	else if (num == 3) genero = Terror;
	else if (num == 4) genero = Drama;
	else if (num == 5) genero = Comedia_romantica;
	return genero;	
}

void escribirGenero(tGenero genero){
	if		(genero == 0) cout << "Ciencia ficcion";
	else if (genero == 1) cout << "Fantasia";
	else if (genero == 2) cout << "Comedia";
	else if (genero == 3) cout << "Terror";
	else if (genero == 4) cout << "Drama";
	else if (genero == 5) cout << "Comedia romantica";
}

ostream& operator<< (ostream &ceaut, tGenero genero){
	if		(genero == 0) ceaut << "Ciencia ficcion";
	else if (genero == 1) ceaut << "Fantasia";
	else if (genero == 2) ceaut << "Comedia";
	else if (genero == 3) ceaut << "Terror";
	else if (genero == 4) ceaut << "Drama";
	else if (genero == 5) ceaut << "Comedia romantica";
	return ceaut;
}