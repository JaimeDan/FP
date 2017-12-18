#include "cliente.h"
#include "listaclientes.h"
#include "funciones.h"



tCliente leerCliente(){
	tCliente cliente;
	string nif, apellidos;
	cout << "Introduzca el NIF del cliente: ";
	leerNif(cliente.nif);
	cout << "Introduzca el nombre del cliente: ";
	getChars(cliente.nombre);
	cout << "Introduzca los apellidos del cliente: ";
	getChars(cliente.apellidos);
	cout << "Introduzca el genero favorito del cliente: " << endl;
	cliente.genero = leerGenero();
	cliente.pelis.cont = 0;
	return cliente;
}

void mostrarCliente (const tCliente cliente, bool mostrarDetalles, const tListaPelis lista){
	bool encontrado = false;
	int posicion;
	cout << endl;
	cout << setfill(' ') << setw(21) << right << "Nombre y apellidos:\t" <<  cliente.nombre << " " << cliente.apellidos << endl << endl;
	cout << setw(21) << right << "NIF:\t" << cliente.nif << endl << endl;
	cout << setw(21) << right << "Genero:\t" << cliente.genero << endl << endl;
	cout << setw(21) << right << "Peliculas vistas:\t" << cliente.pelis.cont << endl << endl << endl;
	if (mostrarDetalles){
		for (int i = 0; i < cliente.pelis.cont; i++){
			posicion = buscarPelicula(lista, cliente.pelis.pelis[i].codigo, 0, lista.cont - 1);
			if (posicion != - 1) encontrado = true;
			if (encontrado){
				cout << *lista.catalogo[posicion] << "\n" << endl;
				cout << "Gusto al cliente? ";
				cliente.pelis.pelis[i].gusto ? cout << "SI": cout << "NO";
				cout << endl << endl;
			}
		}
	}
}

tCliente editarCliente (const tCliente cliente){
	tCliente edicion_cliente = cliente;
	char c;
	int n;
	bool error = true;
	cout << "Introduzca el nombre del cliente: ";
	c = cin.peek();
	if (c == '\n') cin.get(c);
	else getChars(edicion_cliente.nombre);
	cout << "Introduzca los apellidos del cliente: ";
	c = cin.peek();
	if (c == '\n') cin.get(c);
	else getChars(edicion_cliente.apellidos);
	cout << "Introduzca el genero favorito del cliente: " << endl;
	while (error){
		limpiar();
		menuGenero(false);
		c = cin.peek();
		if (c == '\n'){ cin.get(c); error = false;}
		else if (!isdigit(c) || c < '0' || c  > '9') cout << "Valor no valido, introduzcalo de nuevo: ";
		else {
			cin >> n;
			edicion_cliente.genero = leerGenero(n);
			error = false;
		}
	}limpiar();
	return edicion_cliente;
}

void altaVisionado (tCliente& cliente, int codigo, bool gustado){
	//int posicion = cliente.pelis.cont;
	if (cliente.pelis.cont != PELIS_VISTAS){
		cliente.pelis.pelis[cliente.pelis.cont].codigo = codigo;
		cliente.pelis.pelis[cliente.pelis.cont].gusto = gustado;
		cliente.pelis.cont++;
	}else cout << "El size de la lista supera el permitido";
}

void datosVisionado (const tCliente cliente, int codigo, int& veces, int& gustado){
	for (int i = 0; i < cliente.pelis.cont; i++){
		if (codigo == cliente.pelis.pelis[i].codigo){
			veces++;
			if (cliente.pelis.pelis[i].gusto) gustado++;
		}
	}
}