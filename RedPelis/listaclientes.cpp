
#include "listaclientes.h"



bool buscarCliente(tCadena nif, int fin, int& posicion,tCliente& cliente){
	
	bool encontrado;
	if (fin < 0) encontrado = false;
	
	else {
		fstream archivo;
		archivo.open("clientes.dat", ios::in | ios::binary);
		archivo.seekg(0, ios::end);
		int pos = archivo.tellg();
		int numReg = pos / SIZE_CLIENTE;
		archivo.seekg(fin * SIZE_CLIENTE, ios::beg);
		archivo.read( (char *) &cliente, SIZE_CLIENTE);
		if (strcmp(nif, cliente.nif) == 0){
			posicion = fin;
			encontrado = true;
		}
		else encontrado = buscarCliente(nif, fin-1, posicion, cliente);
	}return encontrado;
}

void insertarCliente (tCliente nuevoCliente){

	tCliente cliente;
	fstream archivo;
	archivo.open("clientes.dat", ios::in | ios::out | ios::binary);
	archivo.seekg(0, ios::end);
	int pos = archivo.tellg();
	int numReg = pos / SIZE_CLIENTE;
	pos = 0;
	bool encontrado = false;
	archivo.seekg(0, ios::beg);
	while ((pos < numReg) && !encontrado) {
		archivo.read( (char *) &cliente, SIZE_CLIENTE);
		if (strcmp(cliente.nif, nuevoCliente.nif) > 0) encontrado = true;
		else pos++;
	}
	if (pos == numReg) { // Debe ir al final
		archivo.seekg(0, ios::end);
		archivo.write( (char *) &nuevoCliente, SIZE_CLIENTE);
	}
	else {
		// Hay que hacer hueco
		for (int i = numReg - 1; i >= pos; i--) {
			archivo.seekg(i * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			archivo.seekg((i + 1) * SIZE_CLIENTE, ios::beg);
			archivo.write( (char *) &cliente, SIZE_CLIENTE);
		}
		archivo.seekg(pos * SIZE_CLIENTE, ios::beg);
		archivo.write( (char *) &nuevoCliente, SIZE_CLIENTE);
	}
	archivo.close();
}

bool bajaCliente(tCadena nif){

	tCliente cliente;
	int posicion = 0, fin_lista;
	bool encontrado = false, weba;
	fstream archivo, copia;
	fin_lista = contadorClientes();
	encontrado = buscarCliente(nif, fin_lista, posicion, cliente);
	char oldname[] ="apellidos.dat";
	char newname[] ="clientes.dat";
	if (encontrado){
		archivo.open("clientes.dat", ios::in | ios::out | ios::binary);
		//copiaFicheros();														//crea un archivo auxiliar
		copia.open("apellidos.dat",ios::out | ios::binary);		//borra todo el contenido del archivo auxiliar
		archivo.seekg(0, ios::end);
		copia.seekg(0, ios::beg);
		weba = copia.is_open();
		int pos = archivo.tellg();
		int numReg = pos / SIZE_CLIENTE;
		for (int i = 0; i < numReg; i++) {		//comprueba si el cliente es el que hay que borrar, y en caso contrario lo copia
			archivo.seekg(i * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			if (strcmp(cliente.nif, nif) != 0){
				copia.write( (char *) &cliente, SIZE_CLIENTE);
			}
		}archivo.close();
		copia.close();
		remove("clientes.dat");					//borra el archivo original
		int koh;
		koh = rename("apellidos.dat", "clientes.dat");			//y renombra el otro a clientes.dat
	}
	return encontrado;
}

//contadorClientes retorna el numero de clientes que hay en el archivo de clientes.dat
int contadorClientes(){
	fstream archivo;
	archivo.open("clientes.dat", ios::in | ios::binary);
	archivo.seekg(0, ios::end);
    int pos = archivo.tellg();
    int contador = pos / SIZE_CLIENTE;
	archivo.close();
	return contador;
}