#include "listapelis.h"
#include "funciones.h"

bool listaPeliculasLlena(tListaPelis lista){
	return lista.cont == lista.size;
}

int buscarPelicula(tListaPelis lista, int codigo, int ini, int fin) {
   int pos = -1;
   if (ini <= fin) {
      int mitad = (ini + fin) / 2;
      if (codigo == lista.catalogo[mitad]->codigo)
         pos = mitad;
      else
         if (codigo < lista.catalogo[mitad]->codigo)
            pos = buscarPelicula(lista, codigo, ini, mitad - 1);
         else
            pos = buscarPelicula(lista, codigo, mitad + 1, fin);
   }
   return pos;
}



bool insertarPelicula(tListaPelis& lista, tPelicula pelicula){
   bool ok = true;
      int i = 0;
      while ((i < lista.cont) && (*lista.catalogo[i] < pelicula))
         i++;
      // Insertamos en la posicion i
      for (int j = lista.cont; j > i; j--) // Desplazamos una posicion a la derecha
         lista.catalogo[j] = lista.catalogo[j-1];
	lista.catalogo[i] = new tPelicula;
	*lista.catalogo[i] = pelicula;
    lista.cont++;
   //}
   return ok;
}

bool bajaPelicula(tListaPelis& lista, int codigo){
        int posicion = 0;
        bool encontrado = false;
        posicion = buscarPelicula(lista, codigo, 0, lista.cont - 1);
        if (posicion != -1) encontrado = true;
        if (encontrado) lista.catalogo[posicion]->disponible = false;
        return encontrado;
}