#ifndef LISTAPELIS_H
#define LISTAPELIS_H

#include "peliculas.h"
#include "genero.h"

const int NUM_PELIS = 30;

typedef tPelicula tCatalogo[NUM_PELIS];
typedef bool tBool[NUM_PELIS];

typedef struct {
   tCatalogo catalogo;
   tBool tribul;
   int cont;
} tListaPelis;

bool listaPeliculasLlena(tListaPelis lista);

//bool buscarPelicula(tListaPelis lista, int codigo);

bool buscarPelicula(tListaPelis lista, int codigo, int& posicion);

bool insertarPelicula(tListaPelis& lista, tPelicula pelicula);

bool bajaPelicula(tListaPelis& lista, int codigo);

#endif