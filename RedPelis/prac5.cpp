/*	Practica  5, parte opcional,  realizada por Jesus Aguirre Peman y Jaime Dan Porras Rhee
 *	Ahora se usa un array dinamico de datos dinamicos, se ha implementado la busqueda lineal recursiva y para trabajar con clientes se trabaja directamente desde los archivos
 *
 */


#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <cctype>
using namespace std;

#include "genero.h"
#include "cliente.h"
#include "peliculas.h"
#include "listapelis.h"
#include "funciones.h"
#include "listaclientes.h"

typedef int tMatrizEnteros[12];

//////////////////////////////////////////////////////
/*

PROTOTIPOS DEL MAIN

*/
//////////////////////////////////////////////////////


//////
/*
MENUS Y OPCIONES
*/
//////
int menuPrincipal(string mensaje);

int menuOpcion1_peliculas(string mensaje);

int menuOpcion2_clientes(string mensaje);

int menuOpcion2_clientes(string mensaje);

int menuOpcion3general(string mensaje);
//
void opcion1(tListaPelis& lista);

void opcion2(const tListaPelis pelis);

void opcion3(tListaPelis& lista);
//

 ///////
///////
/*
OPCION PELICULAS
*/
 //////
//////
void baja_pelicula(tListaPelis& lista);

void alta_peli (tListaPelis& lista);

void datos_peli (tListaPelis& lista);

void datos_todas_pelis(tListaPelis& lista);

int menu_todas_pelis();
///////
///////
/*
OPCION CLIENTES
*/
 //////
//////
void nuevo_cliente();

void datos_cliente(const tListaPelis lista_pelis);

void datos_todos_cliente(const tListaPelis lista_pelis);

void editar_cliente(const tListaPelis lista_pelis);

void baja_cliente();

 ///////
///////
/*
OPCION GESTION GENERAL
*/
 //////
//////

void nuevoVisionado(tListaPelis& lista);

void reordenarPorApellidos();

void exportarListaClientes(tListaPelis& lista);

void estadisticasPeliculas(tListaPelis& lista);

 ///////
///////
/*
ARCHIVOS
*/
 //////
//////

void procesarArchivos (ifstream& fClientes, ifstream& fPelis, bool& clientes, bool& pelis);

void inicializarPelis(ifstream& fPelis, tListaPelis& lista_pelis);

void guardarPelis (tListaPelis& lista_pelis);

void guardarListas (tListaPelis& lista_pelis);

void procesarArchivos();

/////////////////////////////////////////////

/*
END PROTOTIPOS
*/

/////////////////////////////////////////////



 ///////////////////////////////////////////
///////////////////////////////////////////

//////////////////////////////////////////////////////
/*

IMPLEMENTACION

*/
//////////////////////////////////////////////////////

 ///////
///////
/*
OPCION PELICULAS
*/
 //////
//////

void baja_pelicula(tListaPelis& lista){
	int codigo;
	bool exito;
	system("cls");
	cout << "\n\n\t\t\t" << "BAJA DE PELICULA" << "\n\n\n\n";
	cout << "Introduzca el codigo de la pelicula: ";
	codigo = getInt();
	exito = bajaPelicula(lista, codigo);
	if (!exito) cout << "No se ha podido realizar la operacion\n";
	else cout << "Operacion realizada con exito!\n";
	EnterParaContinuar();
}


void alta_peli (tListaPelis& lista){
	//bool exito, continua= true;
	int codigo, posicion;
	tPelicula pelicula;
	system("cls");
	cout << "\n\n\t\t\t" << "ALTA DE PELICULA" << "\n\n\n\n";
	if (listaPeliculasLlena(lista)){
		tArrayPelis PtrPeli2;
		lista.size = (lista.size * 3)/2 +1;
		PtrPeli2 = new(tPeliPtr[lista.size]);
		for (int i=0; i< lista.cont; i++)
			PtrPeli2[i] = lista.catalogo[i];
		delete[] lista.catalogo;
		//for (int i=0; i< lista.cont; i++)
		//	lista.catalogo[i] = PtrPeli2[i];
		lista.catalogo = PtrPeli2;
	}
	{
		cout << "Introduzca el codigo de la pelicula: ";
		codigo = getInt();
		while (buscarPelicula(lista, codigo, 0, lista.cont - 1) != -1){
			cout << "Codigo repetido, introduzca el codigo de la pelicula: ";
			codigo = getInt();
		}pelicula = leerPelicula(codigo);
		insertarPelicula(lista, pelicula);
	}
	EnterParaContinuar();
}

void edicionPelicula(tListaPelis& lista){
	int posicion, codigo;
	system("cls");
	cout << "\n\n\t\t\t" << "EDICION DE PELICULA" << "\n\n\n\n";
	cout << "Introduzca el codigo de una pelicula: ";
	codigo = getInt();
	posicion = buscarPelicula(lista, codigo, 0, lista.cont - 1);
	if (posicion != -1){//buscarPelicula retornara -1 si no se encuentra la pelicula
		editarPelicula(*lista.catalogo[posicion]);
		cout << "Pelicula con los nuevos datos: \n";
		cout << *lista.catalogo[posicion];
	}else cout << "Pelicula no encontrada.\n";
	EnterParaContinuar();
}

void datos_peli (tListaPelis& lista){
	int codigo, posicion=0;//hay que inicializar posicion porque a veces el compilador es un poco tontito
	tPelicula pelicula;
	bool exito;
	system ("cls");
	cout << "\n\n\t\t\t" << "DATOS DE PELICULA" << "\n\n\n\n";
	cout << "Introduzca el codigo de la pelicula: ";
	codigo = getInt();
	posicion = buscarPelicula(lista, codigo, 0, lista.cont - 1);
	if (posicion != -1){//buscarPelicula retornara -1 si la pelicula no se ha encontrado
		pelicula = *lista.catalogo[posicion];
		cout << endl << pelicula;
	}else cout << "No se ha encontrado la pelicula con codigo " << codigo << endl;
	EnterParaContinuar();
}

void datos_todas_pelis(tListaPelis& lista){
	int opcion;
	bool continuar = true;
	system ("cls");
	cout << "\n\n\t\t\t" << "DATOS DE TODAS LAS PELICULAS" << "\n\n\n\n";
	while (continuar){//en caso de error, se continuara ejecutando el bucle.
		opcion = menu_todas_pelis();
		continuar = ((opcion != 1) && (opcion != 2));
	}cout << "\n\n";
	if (opcion == 1){
		for (int i = 0; i < lista.cont; i++){
			cout << *lista.catalogo[i] << "\n\n";
		}
	}else if (opcion == 2){
		for (int i = 0; i < lista.cont; i++){
			if (lista.catalogo[i]->disponible) cout << *lista.catalogo[i] << "\n\n";
		}
	}
	limpiar();
	if (lista.cont == 0) cout << "No hay peliculas en la lista";
	EnterParaContinuar();
}

int menu_todas_pelis(){
    char c;
    int opcion;
	system("cls");
	cout << "Ver todas las peliculas o solo las disposibles?\n";
	cout << "1. Todas\n";
	cout << "2. Disponibles\n";
    cout << "Opcion: ";
	limpiar();
    c = cin.peek();
    if (!isdigit(c)) opcion = 3;
	else cin >> opcion;
    return opcion;
}
///////////////////////////////////////
 ///////
///////
/*
OPCION CLIENTES
*/
 //////
//////

void nuevo_cliente(){
	int posicion, fin_lista;
	bool continuar = true;
	tCliente cliente, null;
	system("cls");
	cout << "\n\n\t\t\t" << "NUEVO CLIENTE" << "\n\n\n\n";
	while (continuar){
			cliente = leerCliente();
			fin_lista = contadorClientes();
			if (buscarCliente(cliente.nif,fin_lista, posicion, null)){
				cout << "Ese nif ya existe.\n";
			}else continuar = false;
	}cout << cliente.nombre << " " << cliente.apellidos << ", con NIF " << cliente.nif << " ha sido insertado en la lista.\n";
	insertarCliente(cliente);
	EnterParaContinuar();
}

void datos_cliente(const tListaPelis lista_pelis){
	int fin_lista;
	tCadena nif, si_o_no;
	tCliente cliente;
	int posicion;
	system("cls");
	cout << "\n\n\t\t\t" << "DATOS DE CLIENTE" << "\n\n\n\n";
	cout << "Introduzca un NIF: ";
	leerNif(nif);
	limpiar();
	fin_lista = contadorClientes();
	if (buscarCliente(nif, fin_lista, posicion, cliente)){
		mostrarCliente(cliente, true, lista_pelis);
	}else {
		cout << "No se ha encontrado el NIF buscado..." << endl;
	}
	EnterParaContinuar();
}

void datos_todos_cliente(const tListaPelis lista_pelis){
	tCliente cliente;
	fstream archivo;
	bool no_clientes = true;
	archivo.open("clientes.dat", ios::in | ios::binary);
	system("cls");
	cout << "\n\n\t\t\t" <<setfill(' ') << setw(15) << right << "DATOS DE TODOS LOS CLIENTES" << "\n\n\n\n";
	archivo.read( (char *) &cliente, SIZE_CLIENTE);
		int cuantos = archivo.gcount();
		while (cuantos == SIZE_CLIENTE) {
			no_clientes = false;
			mostrarCliente(cliente, false, lista_pelis);;
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			cuantos = archivo.gcount();
		}if (no_clientes) cout << "No hay clientes en REDPELIS";
		EnterParaContinuar();
}

void editar_cliente(tListaPelis lista_pelis){
	tCadena nif;
	int posicion, fin_lista;
	bool continuar = true;
	tCliente cliente;
	system("cls");
	cout << "\n\n\t\t\t" << "EDITAR CLIENTE" << "\n\n\n\n";
	cout << "Introduzca el NIF del cliente que desea editar: ";
	leerNif(nif);
	fin_lista = contadorClientes();
	if (buscarCliente(nif, fin_lista, posicion, cliente)){
		cliente = editarCliente (cliente);
		fstream archivo;
		archivo.open("clientes.dat", ios::out | ios::in | ios::binary);
		archivo.seekg(posicion * SIZE_CLIENTE, ios::beg);
		archivo.write( (char *) &cliente, SIZE_CLIENTE);
		archivo.seekg(posicion * SIZE_CLIENTE, ios::beg);
		archivo.read( (char *) &cliente, SIZE_CLIENTE);
		/*bajaCliente(nif);
		insertarCliente(cliente);*/
		cout << "Cliente con los nuevos datos: \n";
		mostrarCliente(cliente, false, lista_pelis);
		//archivo.close();

	}else cout << "Ese cliente no existe.\n";
	EnterParaContinuar();

}

void baja_cliente(){
	tCadena nif, nombre, apellidos;
	int posicion, fin_lista;
	tCliente cliente;
	bool encontrado;
	system("cls");
	cout << "\n\n\t\t" << "BAJA DE CLIENTE" << "\n\n\n\n";
	cout << "Introduzca el NIF del cliente que desea eliminar: ";
	leerNif(nif);
	fin_lista = contadorClientes();
	buscarCliente(nif, fin_lista, posicion, cliente); //retorna los datos del cliente para mostrar por pantalla su nombre y apellido
	encontrado = bajaCliente(nif);
	if (encontrado) cout << cliente.nombre << " " << cliente.apellidos << " ha sido eliminado.\n";
	else cout << "Ese cliente no existe, necesito otro objetivo.\n";
	EnterParaContinuar();
}

/////////////////////////////////////
//////
/*
MENUS Y OPCIONES
*/
//////
int menuPrincipal(string mensaje_opcion){
    char c;
    int opcion;
	system("cls");
	cout << "\n\n\t\t\t" << "MENU PRINCIPAL" << "\n\n\n\n" ;
	cout << "\t\t1.- Gestionar peliculas\n";
    cout << "\t\t2.- Gestionar clientes\n";
    cout << "\t\t3.- Gestion general\n";
    cout << "\t\t0.- Salir\n";
    cout << "\t\t" << mensaje_opcion;
    c = cin.peek();
	//si la opción introducida por el usuario no es un dígito, retorna un 4 ya que es una opción no válida
	//que se procesará como tal en el main
    if (!isdigit(c)) opcion = 4;
	else cin >> opcion;
    return opcion;
}

int menuOpcion1_peliculas(string mensaje_opcion){
    char c;
    int opcion;
	system("cls");
	cout << "\n\n\t\t\t" << "GESTION DE PELICULAS" << "\n\n\n\n" ;
    cout << "\t\t1.- Alta de pelicula\n";
    cout << "\t\t2.- Datos de pelicula\n";
    cout << "\t\t3.- Datos de todas las peliculas\n";
    cout << "\t\t4.- Edicion de pelicula\n";
    cout << "\t\t5.- Baja de pelicula\n";
    cout << "\t\t0.- Volver al menu anterior\n";
    cout << "\t\t" << mensaje_opcion;
    c = cin.peek();
    if (!isdigit(c)) opcion = 6;
	else cin >> opcion;
    return opcion;
}

int menuOpcion2_clientes(string mensaje_opcion){
    char c;
    int opcion;
	system("cls");
    cout << "\n\n\t\t\t" << "GESTION DE CLIENTES" << "\n\n\n\n" ;
    cout << "\t\t1.- Nuevo cliente\n";
    cout << "\t\t2.- Datos de cliente\n";
    cout << "\t\t3.- Datos de todos los clientes\n";
    cout << "\t\t4.- Editar cliente\n";
    cout << "\t\t5.- Baja de cliente\n";
    cout << "\t\t0.- Volver al menu anterior\n";
    cout << "\t\t" << mensaje_opcion;
    c = cin.peek();
    if (!isdigit(c)) opcion = 6;
	else cin >> opcion;
    return opcion;
}

int menuOpcion3general(string mensaje_opcion){
    char c;
    int opcion;
	system("cls");
    cout << "\n\n\t\t\t" << "GESTION GENERAL" << "\n\n\n\n" ;
    cout << "\t\t1.- Nuevo visionado\n";
    cout << "\t\t2.- Exportar lista de clientes\n";
    cout << "\t\t3.- Estadisticas de peliculas\n";
    cout << "\t\t0.- Volver al menu anterior\n";
    cout << "\t\t" << mensaje_opcion;
    c = cin.peek();
    if (!isdigit(c)) opcion = 4;
	else cin >> opcion;
    return opcion;
}

/////////////////////////////////////
void opcion1(tListaPelis& lista){
	string mensaje_opcion = OPCION;
	int opcion1;
	bool fin1 = false;
	system("cls");
	while (!fin1){
        limpiar();
        opcion1 = menuOpcion1_peliculas(mensaje_opcion);
		mensaje_opcion = OPCION;
		limpiar();
		if		(opcion1 == 0) fin1 = true;
		else if (opcion1 == 1) alta_peli(lista);
		else if (opcion1 == 2) datos_peli(lista);
		else if (opcion1 == 3) datos_todas_pelis(lista);
		else if (opcion1 == 4) edicionPelicula(lista);
		else if (opcion1 == 5) baja_pelicula(lista);
		else mensaje_opcion = OP_NO_VALIDA;
    }
}

void opcion2(const tListaPelis lista_pelis){
	string mensaje_opcion = OPCION;
	int opcion2;
	bool fin2 = false;
	system("cls");
	while (!fin2){
        limpiar();
        opcion2 = menuOpcion2_clientes(mensaje_opcion);
		mensaje_opcion = OPCION;
		limpiar();
		if		(opcion2 == 0) fin2 = true;
		else if (opcion2 == 1) nuevo_cliente();
		else if (opcion2 == 2) datos_cliente(lista_pelis);
		else if (opcion2 == 3) datos_todos_cliente(lista_pelis);
		else if (opcion2 == 4) editar_cliente(lista_pelis);
		else if (opcion2 == 5) baja_cliente();
		else mensaje_opcion = OP_NO_VALIDA;
    }
}

void opcion3(tListaPelis& lista){
	string mensaje_opcion = OPCION;
	int opcion3;
	bool fin2 = false;
	system("cls");
	while (!fin2){
        limpiar();
        opcion3 = menuOpcion3general(mensaje_opcion);
		mensaje_opcion = OPCION;
		limpiar();
		if		(opcion3 == 0) fin2 = true;
		else if (opcion3 == 1) nuevoVisionado(lista);
		else if (opcion3 == 2) exportarListaClientes(lista);
		else if (opcion3 == 3) estadisticasPeliculas(lista);
		else mensaje_opcion = OP_NO_VALIDA;
    }
	

}

///////////////////////////////////////
//////
/*
GESTION GENERAL
*/
//////

void nuevoVisionado(tListaPelis& lista){
	int codigo, posicion, posicion_peli, indicePelis, fin_lista;
	tCadena nif;
	tCliente cliente;
	bool gustado, exito_peli= false, exito_cliente, disponible, lista_llena;
	system("cls");
	cout << "\n\n\t\t\t" << "NUEVO VISIONADO" << "\n\n\n\n";
	cout << "Introduzca un codigo de pelicula: ";
	codigo = getInt();
	cout << "Introduzca el NIF del cliente: ";
	leerNif(nif);
	cout << "Le ha gustado la pelicula: ";  
	gustado = getYesOrNo();
	fin_lista = contadorClientes();
	exito_cliente = buscarCliente(nif, fin_lista, posicion, cliente);
	posicion_peli = buscarPelicula(lista, codigo, 0, lista.cont - 1);
	if (posicion_peli != -1) exito_peli = true;
	if (exito_peli) disponible = lista.catalogo[posicion_peli]->disponible;
	else disponible = false;
	if (exito_cliente) lista_llena = cliente.pelis.cont >= PELIS_VISTAS;
	else lista_llena = false;

	if (exito_cliente && exito_peli && disponible && !lista_llena){
		indicePelis = cliente.pelis.cont;
		cliente.pelis.pelis[indicePelis].codigo = codigo;
		cliente.pelis.pelis[indicePelis].gusto = gustado;
		cliente.pelis.cont++;
		cout << "\n\nPelicula: " << lista.catalogo[posicion_peli]->titulo << endl << endl;
		cout << "Codigo de pelicula: " <<  lista.catalogo[posicion_peli]->codigo << endl << endl;
		cout << "Ha sido vista por: " << cliente.nombre << " " << cliente.apellidos << " y ";
		gustado ? cout << " si " : cout << " no ";
		cout << "le ha gustado.\n\n";
		fstream archivo;
		archivo.open("clientes.dat", ios::out | ios::in | ios::binary);
		archivo.seekg(posicion * SIZE_CLIENTE, ios::beg);
		archivo.write( (char *) &cliente, SIZE_CLIENTE);
		archivo.seekg(posicion * SIZE_CLIENTE, ios::beg);
		archivo.read( (char *) &cliente, SIZE_CLIENTE);
		archivo.close();
	}
	else {
		if (lista_llena) cout << "La lista de peliculas del cliente esta llena " << endl;
		else{
			if (!exito_cliente) cout << "No se ha encontrado el cliente con nif " << nif << endl;
			if (!exito_peli) cout << "No se ha encontrado la pelicula con codigo " << codigo << endl;
			else if (!disponible) cout << "La pelicula con codigo " << codigo << " no esta disponible " << endl;
			cout << "La operacion no ha podido realizarse con exito\n";
		}
	}
	EnterParaContinuar();
}

void reordenarPorApellidos(){
	fstream archivo;
	copiaFicheros();
	archivo.open("apellidos.dat", ios::in | ios::out | ios::binary);
	archivo.seekg(0, ios::end);
	int pos = archivo.tellg();
	int numcliente = pos / SIZE_CLIENTE;
	tCliente clienMenor, cliente;		//ordenacion por seleccion directa
	for (int i = 0; i < numcliente - 1; i++){
		int menor = i;
		for (int j = i + 1; j < numcliente; j++){
			archivo.seekg(menor * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &clienMenor, SIZE_CLIENTE);
			archivo.seekg(j * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			if (strcmp(cliente.apellidos, clienMenor.apellidos) < 0)
			menor = j;
		}
		if (menor > i) { // Intercambiamos
			archivo.seekg(menor * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &clienMenor, SIZE_CLIENTE);
			archivo.seekg(i * SIZE_CLIENTE, ios::beg);
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			archivo.seekg(menor * SIZE_CLIENTE, ios::beg);
			archivo.write( (char *) &cliente, SIZE_CLIENTE);
			archivo.seekg(i * SIZE_CLIENTE, ios::beg);
			archivo.write( (char *) &clienMenor, SIZE_CLIENTE);
		}
	}
	archivo.close();
	//remove("apellidos.dat");
}

void exportarListaClientes(tListaPelis& lista){
	ofstream fout;
	tCadena nombre_archivo;
	system("cls");
	cout << "\n\n\t\t\t" << "EXPORTAR LISTA DE CLIENTES" << "\n\n\n\n";
	cout << "Introduzca el nombre del archivo al que desea exportar la lista de clientes: \n";
	getChars(nombre_archivo);
	fout.open(nombre_archivo);
	if (!fout.is_open()) cout << "Error, no se ha podido crear el archivo\n";
	else{
		reordenarPorApellidos();
		tCliente cliente;
		fstream archivo;
		archivo.open("apellidos.dat", ios::in | ios::binary);
		archivo.seekg(0, ios::end);
		int pos = archivo.tellg();
		int contador = pos / SIZE_CLIENTE;
		archivo.seekg(0, ios::beg);
		for (int i=0; i< contador; i++){
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			fout << cliente.apellidos << ", ";
			fout << cliente.nombre << endl;
			fout << "NIF: " << cliente.nif << endl;
			fout << "Numero de peliculas vistas: " << cliente.pelis.cont << "\n\n";
		}
		remove ("apellidos.dat");
		fout.close();
		cout << "Operacion realizada con exito\n";
	} EnterParaContinuar();
}	

void estadisticasPeliculas(tListaPelis& lista){
	int contador = 0, codigo, veces, gustado;
	tCliente cliente;
	fstream archivo;
	system("cls");
	cout << "\n\n\t\t\t"  << "ESTADISTICA DE PELICULAS" << "\n\n\n\n";	
	for (int i = 0; i< lista.cont; i++){
		archivo.open("clientes.dat", ios::in | ios::binary);
		codigo = lista.catalogo[i]->codigo;
		veces = 0, gustado = 0;
		//archivo.read( (char *) &cliente, SIZE_CLIENTE);
		//int cuantos = archivo.gcount();
		int cuantos = contadorClientes();
		/*while (cuantos == SIZE_CLIENTE){*/
		for(int i=0; i< cuantos; i++){
			archivo.read( (char *) &cliente, SIZE_CLIENTE);
			datosVisionado (cliente, codigo, veces, gustado);
		}
		cout << setfill('_') <<  setw(40) << "_" << endl << endl;
		cout << lista.catalogo[i]->titulo << endl << endl;
		cout << "\tHa sido vista " << veces << " veces.\n\n";
		if (veces != 0){
			cout << "\t" << "A los clientes les ha gustado un total de  " << gustado << " veces.\n\n";
			cout << "\t" << setprecision(4) << ((float(gustado)/float(veces))*100) << "% de votos positivos.\n\n";
		}archivo.close();
	}setfill(' ');	
	EnterParaContinuar();
}


 //////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////
/*
ARCHIVOS
*/
//////

bool inicializarPelis(tListaPelis& lista_pelis){
	bool exito = true;
	fstream archivo;
	tPelicula pelicula;
	tPeliPtr PeliPointer;
	archivo.open("pelis.dat", ios::in | ios::binary);
	archivo.seekg(0, ios::end);
    int pos = archivo.tellg();
    int numReg = pos / SIZE_PELI;
	int size = ((numReg / 10) + 1) * 10;
	lista_pelis.cont = 0;
	lista_pelis.catalogo = new tPeliPtr[size];
	lista_pelis.size = size;
	archivo.seekg(0, ios::beg);
	lista_pelis.catalogo[0] = new tPelicula;
	archivo.read( (char *) lista_pelis.catalogo[0], SIZE_PELI);
	int cuantos = archivo.gcount();
	int i = 1;
	if (cuantos != SIZE_PELI) exito = false;
	while (cuantos == SIZE_PELI) {
		lista_pelis.catalogo[i] = new tPelicula;
		archivo.read( (char *) lista_pelis.catalogo[i], SIZE_PELI);
		i++;
		lista_pelis.cont++;
		cuantos = archivo.gcount();
	}
	archivo.close();
	return exito;
}

void guardarPelis (tListaPelis& lista_pelis){
	fstream archivo;
	archivo.open("pelis.dat", ios::out | ios::binary);
	for (int i = 0; i < lista_pelis.cont; i++)
		archivo.write( (char *) lista_pelis.catalogo[i], SIZE_PELI);
	
	archivo.close();
}


void copiaFicheros() {
   tCliente cliente;
   fstream archivo, copia;
   archivo.open("clientes.dat", ios::in | ios::binary);
   copia.open("apellidos.dat", ios::out | ios::binary);
   archivo.read( (char *) &cliente, SIZE_CLIENTE);
   int cuantos = archivo.gcount();
   while (cuantos == SIZE_CLIENTE) {
	  copia.write( (char *) &cliente, SIZE_CLIENTE);
      archivo.read( (char *) &cliente, SIZE_CLIENTE);
      cuantos = archivo.gcount();
   }
   archivo.close();
   copia.close();
}

//bool inicializarClientes(tListaClientes& lista_clientes){
//	bool exito = true;
//	fstream archivo;
//	archivo.open("clientes.dat", ios::in | ios::binary);
//	archivo.seekg(0, ios::end);
//    int pos = archivo.tellg();
//    int numReg = pos / SIZE_CLIENTE;
//	int size = ((numReg / 10) + 1) * 10;
//	lista_clientes.contador = 0;
//	lista_clientes.todosClientes = new tCliente[size];
//	lista_clientes.size = size;
//	archivo.seekg(0, ios::beg);
//	archivo.read( (char *) &lista_clientes.todosClientes[0], SIZE_CLIENTE);
//	int cuantos = archivo.gcount();
//	int i = 1;
//	if (cuantos != SIZE_CLIENTE) exito = false;
//	while (cuantos == SIZE_CLIENTE) {
//		archivo.read( (char *) &lista_clientes.todosClientes[i], SIZE_CLIENTE);
//		i++;
//		lista_clientes.contador++;
//		cuantos = archivo.gcount();
//	}
//	archivo.close();
//	return exito;
//}
//
//void guardarClientes (tListaClientes& lista_clientes){
//	
//	fstream archivo;
//	archivo.open("clientes.dat", ios::out | ios::binary);
//	for (int i = 0; i < lista_clientes.contador; i++)
//		archivo.write( (char *) &lista_clientes.todosClientes[i], SIZE_CLIENTE);
//	
//	archivo.close();
//}

//
//void guardarListas (tListaPelis& lista_pelis, tListaClientes& lista_clientes){
//	//guardarPelis(lista_pelis);
//	//guardarClientes(lista_clientes);
//}
//////////////////////////////////////////////////////
/*

END IMPLEMENTACION

*/
//////////////////////////////////////////////////////

	
int main(){
	bool exito_clientes, exito_pelis;
	tListaPelis lista_pelis;
	exito_pelis = inicializarPelis(lista_pelis);
	if (!exito_pelis){
		cout << "Se ha comenzado con una lista vacia de peliculas.\n";
		lista_pelis.cont = 0;
		lista_pelis.size = INIT_SIZE;
		lista_pelis.catalogo = new tPeliPtr[INIT_SIZE];
	}else cout << "Se ha encontrado la lista de peliculas";
	EnterParaContinuar();
	int opcion;
	string mensaje_opcion = OPCION;
	bool fin = false;
	while (!fin){
        limpiar();
        opcion = menuPrincipal(mensaje_opcion);
		limpiar();
		mensaje_opcion = OPCION;
		if		(opcion == 0) fin = true;
		else if (opcion == 1) opcion1(lista_pelis);
		else if (opcion == 2) opcion2(lista_pelis);
		else if (opcion == 3) opcion3(lista_pelis);
		else mensaje_opcion = OP_NO_VALIDA;
	}guardarPelis(lista_pelis);
	return 0;
}