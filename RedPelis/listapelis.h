#ifndef LISTAPELIS_H
#define LISTAPELIS_H

#include "peliculas.h"
#include "genero.h"


typedef tPelicula *tPeliPtr;

const int SIZE_PELI = sizeof(tPelicula);

typedef tPeliPtr *tArrayPelis;



typedef struct {
   tArrayPelis catalogo;
   int cont;
   int size;
} tListaPelis;

bool listaPeliculasLlena(tListaPelis lista);

void edicionPelicula(tListaPelis& lista);

int buscarPelicula(tListaPelis lista, int codigo, int ini, int fin);

bool insertarPelicula(tListaPelis& lista, tPelicula pelicula);

bool bajaPelicula(tListaPelis& lista, int codigo);



#endif