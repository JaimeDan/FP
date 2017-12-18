#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <sstream>
using namespace std;

#include "genero.h"
#include "peliculas.h"
#include "listapelis.h"

#include <string>

typedef struct {
	string nif;
	string nombre;
	string apellidos;
	tGenero genero;
	tListaPelis pelis;
} tCliente;

tCliente leerCliente ();

void mostrarCliente (const tCliente cliente, bool mostrarDetalles, tListaPelis lista);

void editarCliente (tCliente& cliente);

void altaVisionado (tCliente& cliente, int codigo);

void datosVisionado (const tCliente cliente, int codigo, int& veces, int& gustado);

string leeNif();

bool dniOK(string dni);

char letraDNI(int dni);

ostream &operator<<(ostream ceaut, tCliente cliente);





#endif