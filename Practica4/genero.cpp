#include <iostream>
using namespace std;

#include "genero.h"

void limpiar(){
	cin.clear();
	cin.sync();
}


int menuGenero(){
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
    c = cin.peek();
    if (!isdigit(c)) opcion = 7;
	else cin >> opcion;
    return opcion;
}
tGenero leerGenero(){
	tGenero genero;
	int opcion_gen;
	bool fin = true;
	do{
        limpiar();
        opcion_gen = menuGenero();
		limpiar();
		if		(opcion_gen == 1) genero = ciencia_ficcion;
		else if (opcion_gen == 2) genero = fantasia;
		else if (opcion_gen == 3) genero = comedia;
		else if (opcion_gen == 4) genero = terror;
		else if (opcion_gen == 5) genero = drama;
		else if (opcion_gen == 6) genero = comedia_romantica;
		else{
			cout << "Opcion no valida! Introduzcala de nuevo: ";
			fin = false;
		}
    } while (!fin);
	//abajo con while
	/*
	bool fin = false;
	while (!fin){
		limpiar();
		opcion_gen = menuGenero();
		limpiar();
		fin = true;
		if		(opcion_gen == 1) genero = ciencia_ficcion;
		else if (opcion_gen == 2) genero = fantasia;
		else if (opcion_gen == 3) genero = comedia;
		else if (opcion_gen == 4) genero = terror;
		else if (opcion_gen == 5) genero = drama;
		else if (opcion_gen == 6) genero = comedia_romantica;
		else{
			cout << "Opcion no valida! Introduzcala de nuevo: ";
			fin = false;
		}
	}
	*/
	return genero;	
}

void escribirGenero(tGenero genero){
	if		(genero == 0) cout << "ciencia ficcion";
	else if (genero == 1) cout << "fantasia";
	else if (genero == 2) cout << "comedia";
	else if (genero == 3) cout << "terror";
	else if (genero == 4) cout << "drama";
	else if (genero == 5) cout << "comedia romantica";
}

ostream& operator<< (ostream &ceaut, tGenero genero){
	if		(genero == 0) ceaut << "ciencia ficcion";
	else if (genero == 1) ceaut << "fantasia";
	else if (genero == 2) ceaut << "comedia";
	else if (genero == 3) ceaut << "terror";
	else if (genero == 4) ceaut << "drama";
	else if (genero == 5) ceaut << "comedia romantica";
	return ceaut;
}