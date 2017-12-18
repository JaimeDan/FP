#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

const string ERROR = "Error al introducir datos, introduzcalos de nuevo.\n";
const string OP_NO_VALIDA = "Opcion no valida! Introduzcala de nuevo: ";
const string OPCION = "Opcion: ";
const int SIZE_CADENA = 80;
const int INIT_SIZE = 10;

typedef char tCadena[SIZE_CADENA];


int contadorClientes();

void getChars(tCadena& cadena);

void leerNif(tCadena& cadena);

int getInt();

double getDouble();

char getChar();

void limpiar();

void EnterParaContinuar();

bool getYesOrNo();

bool dniOK(const tCadena dni);

char letraDNI(int dni);

void copiaFicheros();

#endif