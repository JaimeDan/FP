#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H
#include "cliente.h"



const int SIZE_CLIENTE = sizeof(tCliente);//size del registro tCliente

bool buscarCliente(tCadena nif, int fin,int& posicion, tCliente& cliente);

void insertarCliente(tCliente cliente);

bool bajaCliente(tCadena nif);

//se ha añadido esta funcion a listaclientes.h porque sirve para leer el archivo y ver cuantos clientes hay en la lista
int contadorClientes();


#endif