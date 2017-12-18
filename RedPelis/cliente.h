#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
using namespace std;

#include "genero.h"
#include "peliculas.h"
#include "listapelis.h"
//#include "listaclientes.h"

//maximo de peliculas que puede tener un cliente
const int PELIS_VISTAS = 40;

//estructura pelicula para incluirla en la estructura cliente
typedef struct{
	int codigo;
	bool gusto;
}tPeliCliente;

//array de la estructura de peliculas
typedef tPeliCliente tPelisVistas[PELIS_VISTAS];

//estructura con el array de peliculas y el contador
typedef struct {
   tPelisVistas pelis;
   int cont;
} tListaPelisVistas;

//estructura con el cliente
typedef struct {
	tCadena nif;
	tCadena nombre;
	tCadena apellidos;
	tGenero genero;
	tListaPelisVistas pelis;
} tCliente;

//Funcion leerCliente
//Lee los campos nif, nombre, apellidos y genero e inicializa el contador del array de peliculas a 0
//@return, retorna el cliente
tCliente leerCliente ();

//Funcion mostrarCliente
//muestra un cliente por consola
//@const tCliente cliente, estructura con los datos del cliente que se quiere mostrar
//@bool mostrarDetalles, booleano que indica si se debe mostrar o no la lista de peliculas que ha visto el cliente
//@tListaPelis lista, lista con las peliculas para poder mostrar las peliculas que ha visto el cliente
void mostrarCliente (const tCliente cliente, bool mostrarDetalles, tListaPelis lista);

//Funcion tCliente editarCliente
//recibe un cliente y edita los campos nombre, apellidos y genero
//@const tCliente cliente, cliente que se recibe de entrada
//@return tCliente, retorna el cliente con los campos editados
tCliente editarCliente (const tCliente cliente);

//funcion altaVisionado
//recibe un codigo y un booleano, y escribe en la listapelis de clientes el codigo de la pelicula y si le ha gustado  o no
//@int codigo, codigo de la pelicula
//@bool gustado, booleano que indica si la pelicula ha gustado o no
//@tCliente& cliente, estructura de cliente en la que se realizan los cambios
void altaVisionado (tCliente& cliente, int codigo, bool gustado);

//funcion datosVisionado
//calcula, para un cierto cliente y una cierta pelicula, las veces que la ha visto y las veces que le ha gustado
//@const tCliente cliente, estructura con el cliente
//@int codigo, codigo de la pelicula
//@int& veces, al valor de entrada se le suman las veces que el cliente ha visto la pelicula
//@int& gustado, al valor de entrada se le suman las veces que al cliente le ha gustado la pelicula
void datosVisionado (const tCliente cliente, int codigo, int& veces, int& gustado);





#endif