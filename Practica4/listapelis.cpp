#include "listapelis.h"


bool listaPeliculasLlena(tListaPelis lista){
	bool llena;
	if (lista.cont == NUM_PELIS) llena = true;
	else llena = false;
	return llena;
}

/*bool buscarPelicula(tListaPelis lista, int codigo){
	bool encontrado = false;
	//busqueda en lista, la lista esta ordenada x codigo
	return encontrado;
}*/

bool buscarPelicula(tListaPelis lista, int codigo, int& posicion){
   int ini = 0, fin = lista.cont - 1, mitad;
   bool encontrado = false;
   while ((ini <= fin) && !encontrado) {
      mitad = (ini + fin) / 2; // División entera
      if (codigo == lista.catalogo[mitad].codigo)
         encontrado = true;
      else if (codigo < lista.catalogo[mitad].codigo)
         fin = mitad - 1;
      else
         ini = mitad + 1;
   }
   if (encontrado)
      posicion = mitad;
   return encontrado;
}

bool insertarPelicula(tListaPelis& lista, tPelicula pelicula){
   bool ok = true;
   if (listaPeliculasLlena(lista)) ok = false; // lista llena
   else {
      int i = 0;
      while ((i < lista.cont) && (lista.catalogo[i] < pelicula))
         i++;
      // Insertamos en la posición i
      for (int j = lista.cont; j > i; j--) // Desplazamos una posición a la derecha
         lista.catalogo[j] = lista.catalogo[j-1];
      lista.catalogo[i] = pelicula;
      lista.cont++;
   }
   return ok;
}

bool bajaPelicula(tListaPelis& lista, int codigo){
	int posicion = 0;
	bool encontrado = false;
	encontrado = buscarPelicula(lista, codigo, posicion);
	if (encontrado) lista.catalogo[posicion].disponible = false;
	return encontrado;
}