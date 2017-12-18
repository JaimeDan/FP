#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

#include "genero.h"
#include "peliculas.h"
#include "listapelis.h"

//const int NUM_PELIS = 30;
const int PELIS_VISTAS = 40;

/*typedef enum tGenero {ciencia_ficcion, fantasia, comedia, terror, drama, comedia_romantica};
typedef struct {
	int codigo;
	string titulo;
	tGenero genero;
	double duracion;
	double precio;
	bool disponible;
} tPelicula;*/
/*typedef tPelicula tCatalogo[NUM_PELIS];
typedef struct {
   tCatalogo catalogo;
   int cont;
} tListaPelis;*/
typedef int tMatrizEnteros[12];

typedef struct{
	int codigo;
	bool gusto;
}tPeliCliente;
typedef tPeliCliente tPelisVistas[PELIS_VISTAS];
typedef struct {
   tPelisVistas pelis;
   int cont;
} tListaPelisVistas;
typedef struct {
	string nif;
	string nombre;
	string apellidos;
	tGenero genero;
	tListaPelisVistas pelis;
} tCliente;
typedef tCliente tTodosClientes[NUM_PELIS];
typedef struct {
   tTodosClientes todosClientes;
   int contador;
} tListaClientes;

/*bool operator>(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo > opDer.codigo;
}

bool operator<(tPelicula opIzq, tPelicula opDer) {
   return opIzq.codigo < opDer.codigo;
}*/

int menu_todas_pelis();
/*bool dniOK(string dni) {
   bool ok = true;
   if (dni.size() != 8)
      ok = false;
   else
      for (int i = 0; i < dni.size(); i++)
         if ((dni.at(i) < '0') || (dni.at(i) > '9'))
            ok = false;
   return ok;
}

char letraDNI(int dni){
	int suma = 0, digito;
	char letra;
	char c[24] = "TRWAGMYFPDXBNJZSQVHLCKE";
	while (dni >= 0){
		digito = dni%10;
		dni = (dni - digito)/10;
		suma += digito;
	}suma = suma%23;
	letra = c[suma];
	return letra;	
}

string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
string leeNif() {
	string dni;
	stringstream ss;
	int dni_n;
	char letra;
	bool OK = false;
	//do {
	while (!OK){
		cout << "D.N.I. (8 digitos): ";
		limpiar();
		cin >> dni_n;
		ss << dni_n;
		dni = ss.str();
		OK = dniOK(dni);
	}
	//} while (!dniOK(dni));
	/*do {
		cout << "Letra: ";
		cin.sync();
		cin >> letra;
		letra = toupper(letra);
	} while ((letra < 'A') || (letra > 'Z'));
	*//*
	letra = letraDNI(dni_n);
	dni = dni + letra;
	return dni;
}
*/
/*int menuGenero(){
	char c;
	int opcion;
	cout << "Seleccione el genero de la pelicula de entre los siguientes:\n";
	cout << "1.- Ciencia-ficcion\n";
    cout << "2.- Fantasia\n";
    cout << "3.- Comedia\n";
    cout << "4.- Terror\n";
    cout << "5.- Drama\n";
    cout << "6.- Comedia-romantica\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 7;
	else cin >> opcion;
    return opcion;
}
tGenero leerGenero(){
	tGenero genero;
	int opcion_gen;
	bool fin = true;
	do{
        limpiar();
        opcion_gen = menuGenero();
		limpiar();
		if		(opcion_gen == 1) genero = ciencia_ficcion;
		else if (opcion_gen == 2) genero = fantasia;
		else if (opcion_gen == 3) genero = comedia;
		else if (opcion_gen == 4) genero = terror;
		else if (opcion_gen == 5) genero = drama;
		else if (opcion_gen == 6) genero = comedia_romantica;
		else{
			cout << "Opcion no valida! Introduzcala de nuevo: ";
			fin = false;
		}
    } while (!fin);
	return genero;	
}
void escribirGenero(tGenero genero){
	if (genero == 0) cout << "ciencia ficcion";
	else if (genero == 1) cout << "fantasia";
	else if (genero == 2) cout << "comedia";
	else if (genero == 3) cout << "terror";
	else if (genero == 4) cout << "drama";
	else if (genero == 5) cout << "comedia romantica";
}*/

/*tPelicula leerPelicula(){
	tPelicula pelicula;
	
	do{
		cout << "Introduzca el codigo de la pelicula: ";
		limpiar();
		cin >> pelicula.codigo;		
	}while (cin.fail());
	
	do{
		cout << "Introduzca el titulo de la pelicula: ";
		limpiar();
		cin >> pelicula.titulo;
	}while (cin.fail());
	do{
		cout << "Introduzca el genero de la pelicula: ";
		limpiar();
		pelicula.genero = leerGenero();
	}while (cin.fail());
	do{
		cout << "Introduzca la duracion de la pelicula: ";
		limpiar();
		cin >> pelicula.duracion;
	}while (cin.fail());
		do{
		cout << "Introduzca el precio de la pelicula: ";
		limpiar();
		cin >> pelicula.precio;
	}while (cin.fail());

	pelicula.disponible = true; 
	return pelicula;
}*/

/*
bool listaPeliculasLlena(tListaPelis lista){
	bool llena;
	if (lista.cont == NUM_PELIS) llena = true;
	else llena = false;
	return llena;
}*/
/*
bool buscarPelicula(tListaPelis lista, int codigo){
	bool encontrado = false;
	//busqueda en lista, la lista esta ordenada x codigo
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

bool bajaPelicula(tListaPelis& lista, int codigo){
	int posicion = 0;
	bool encontrado = false;
	encontrado = buscarPelicula(lista, codigo, posicion);
	if (encontrado) lista.catalogo[posicion].disponible = false;
	return encontrado;
}*/

void baja_pelicula(tListaPelis& lista){
	int codigo;
	bool exito;
	do{
		limpiar();
		"Introduzca el codigo de la pelicula: ";
		cin >> codigo;
	}while (cin.fail());
	exito = bajaPelicula(lista, codigo);
	if (!exito) cout << "No se ha podido realizar la operacion\n";
	else cout << "Operacion realizada con exito!";
}

bool alta_peli (tListaPelis& lista){
	bool exito;
	tPelicula pelicula;
	if(listaPeliculasLlena(lista)){
		pelicula = leerPelicula();
		insertarPelicula(lista, pelicula);
		exito = true;
	}
	else exito = false;
	return exito;
}

bool datos_peli (tListaPelis& lista){
	int codigo, posicion;
	tPelicula pelicula;
	bool exito;
	cout << "Introduzca el codigo de la pelicula: ";
	do{
		cin >> codigo;
		limpiar();
	}while (cin.fail());
	exito = buscarPelicula(lista, codigo, posicion);
	pelicula = lista.catalogo[posicion];
	if (exito) mostrarPelicula(pelicula);
	return exito;
}

void datos_todas_pelis(tListaPelis& lista){
	int opcion;
	do{
		opcion = menu_todas_pelis();
	}while ((opcion!= 1) || (opcion != 2));
	if (opcion == 1){
		for (int i = 0; i < NUM_PELIS; i++)
			mostrarPelicula(lista.catalogo[i]);
		
	}else if (opcion == 2){
		for (int i = 0; i < NUM_PELIS; i++){
			if (lista.catalogo[i].disponible == true)
			mostrarPelicula(lista.catalogo[i]);
		}
	}
}
/*
void editarPelicula(tListaPelis& lista){
	int posicion, codigo;
	tPelicula pelicula;
	cout << "Introduzca el codigo de una pelicula: ";
	cin >> codigo;
	buscarPelicula(lista, codigo, posicion);


}
*/
int menu_todas_pelis(){
    char c;
    int opcion;
	cout << "Ver todas las peliculas o solo las disposibles?\n";
	cout << "1. Todas\n";
	cout << "2. Disponibles\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 3;
	else cin >> opcion;
    return opcion;
}

int menuPrincipal(){
    char c;
    int opcion;
    cout << "1.- Gestionar peliculas\n";
    cout << "2.- Gestionar clientes\n";
    cout << "3.- Gestion general\n";
    cout << "0.- Salir\n";
    cout << "Opcion: ";
    c = cin.peek();
	//si la opción introducida por el usuario no es un dígito, retorna un 4 ya que es una opción no válida
	//que se procesará como tal en el main
    if (!isdigit(c)) opcion = 4;
	else cin >> opcion;
    return opcion;
}
int menuOpcion1_peliculas(){
    char c;
    int opcion;
    cout << "1.- Alta de pelicula\n";
    cout << "2.- Datos de pelicula\n";
    cout << "3.- Datos de todas las peliculas\n";
    cout << "4.- Edicion de pelicula\n";
    cout << "5.- Baja de pelicula\n";
    cout << "0.- Volver al menu anterior\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 6;
	else cin >> opcion;
    return opcion;
}

int menuOpcion2_clientes(){
    char c;
    int opcion;
    cout << "1.- Nuevo cliente\n";
    cout << "2.- Datos de cliente\n";
    cout << "3.- Datos de todos los clientes\n";
    cout << "4.- Editar cliente\n";
    cout << "5.- Baja de cliente\n";
    cout << "0.- Volver al menu anterior\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 6;
	else cin >> opcion;
    return opcion;
}

int menuOpcion3_general(){
    char c;
    int opcion;
    cout << "1.- Nuevo visionado\n";
    cout << "2.- Exportar lista de clientes\n";
    cout << "3.- Estadisticas de peliculas\n";
    cout << "0.- Volver al menu anterior\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 4;
	else cin >> opcion;
    return opcion;
}

void opcion1(tListaPelis& lista){
	int opcion1;
	bool fin1 = false;
	while (!fin1){
        limpiar();
        opcion1 = menuOpcion1_peliculas();
		limpiar();
		if		(opcion1 == 0) fin1 = true;
		else if (opcion1 == 1) alta_peli(lista);
		else if (opcion1 == 2) datos_peli(lista);
		else if (opcion1 == 3) datos_todas_pelis(lista);
		//else if (opcion1 == 4) editarPelicula(lista);
		else if (opcion1 == 5) baja_pelicula(lista);

		else cout << "Opcion no valida! Introduzcala de nuevo: ";
    }
}
/*tCliente leerCliente(){
	tCliente cliente;
	string nif, apellidos;
	do{
		cout << "Introduzca el NIF del cliente: ";
		limpiar();
		cliente.nif = leeNif();		
	}while (cin.fail());
	do{
		cout << "Introduzca el nombre del cliente: ";
		limpiar();
		cin >> cliente.nombre;
	}while (cin.fail());
	do{
		cout << "Introduzca los apellidos del cliente: ";
		limpiar();
		getline(cin, apellidos);
	}while (cin.fail());
	do{
		cout << "Introduzca el genero favorito del cliente: ";
		limpiar();
		cliente.genero = leerGenero();
	}while (cin.fail());
	cliente.pelis.cont = 0;
	return cliente;
}*/
void opcion2(tListaPelis& lista){
	int opcion2;
	bool fin2 = false;
	while (!fin2){
        limpiar();
        opcion2 = menuOpcion2_clientes();
		limpiar();
		if		(opcion2 == 0) fin2 = true;
		//else if (opcion2 == 1) nuevo_cliente();
		//else if (opcion2 == 2) datos_cliente();
		//else if (opcion2 == 3) datos_todos_cliente();
		//else if (opcion2 == 4) editar_cliente();
		//else if (opcion2 == 5) baja_cliente();

		else cout << "Opcion no valida! Introduzcala de nuevo: ";
    }
}


void opcion3(tListaPelis& lista){

}
ostream& operator<< (ostream &ceaut, tMatrizEnteros matrix){
	for (int i=0; i<12; i++)
		ceaut << matrix[i] << " ";
	return ceaut;
}

int main(){
	tListaPelis lista;
	tPelicula peli;
	peli.codigo = 12;
	peli.disponible = true;
	peli.duracion = 1.4;
	peli.genero = ciencia_ficcion;
	peli.precio = 12;
	peli.titulo = "matriz";
	cout << peli;
	int opcion;
	bool fin = false;
	while (!fin){
        limpiar();
        opcion = menuPrincipal();
		limpiar();
		if		(opcion == 0) fin = true;
		else if (opcion == 1) opcion1(lista);
		else if (opcion == 2) opcion2(lista);
		else if (opcion == 3) opcion3(lista);
		else cout << "Opcion no valida! Introduzcala de nuevo: ";
    }
	return 0;
}
