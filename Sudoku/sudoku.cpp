/*  Práctica realizada por: Jaime Dan Porras Rhee y Jesús Aguirre Pemán
 *  Práctica 3, sudoku
 *  El programa permite al usuario gestionar un sudoku.
 *  Se pueden realizar las siguientes operaciones:
 *  Ver los posibles valores para una casilla, rellenar una casilla, borrar una casilla, ver los valores incorrectos, 
 *		reiniciar el tablero, y rellenar las casillas con un unico valor posible
 */



#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
//#include "F:\Practica 3\Practica 3\ventanaGrafica.h"
using namespace std;

///////////////////////////////////////////////////////////


const int DIM = 9;
const int RAIZ_DIM = 3;

typedef int tIntTablero[DIM][DIM];//array 9x9 que guarda los valores de cada casilla
typedef bool tBoolTablero[DIM][DIM];//array booleano de dimension 9x9 para guardar los valores iniciales del sudoku
typedef int tIntCandidatos[DIM];//array que guarda los posibles candidatos para una casilla

//estructura que contiene un contador que guarda el numero de casillas rellenas, 
//	un tablero sudoku y un tablero booleano con los valores iniciales
typedef struct{
    int contador;
    tIntTablero Tablero;
    tBoolTablero boolTablero;
}tSudoku;

//estructura con un array que guarda los posibles valores para una casilla y un contador con el numero de posibles candidatos
typedef struct{
	int contador;
	tIntCandidatos lista;
}tCandidatos;



///////////////////////////////////////////////////////////



//function prototype

//limpiar, limpia el buffer y el flag de error
void limpiar();

// muestra el menu, retorna la opcion elegida
int mostrarMenu ();

//mostrar sudoku por pantalla 
//@tSudoku sudoku, array con el sudoku
void MostrarSudoku (const tSudoku sudoku);

//abrir archivos
//@ifstream fSudoku, flujo para leer el archivo con el sudoku original
//@ifstream fSolucion, flujo para leer el archivo con la solucion del sudoku
void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion);

//inicializa tableros
//@fSudoku, para el archivo con el sudoku inicial, @fSolucion para el archivo con la solucion
//@tSudoku, struct con el sudoku, @tIntTablero, array bidimensional con la solucion
//@bool error indica si el archivo con el sudoku inicial contiene errores
void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, tIntTablero& solucion, bool& error);

//valida el numero introducido por teclado por el usuario
int comprobarNumero();

//inicializa la lista de candidatos a 0 y el contador que indica posicion a 0
//@tCandidatos, array con los candidatos
void inicializarCandidatos(tCandidatos& posibles);

//mira los posibles valores para una celda
//@tSudoku, struct con el sudoku
//@int fila y columna, valores de entrada, tCandidatos posibles, array con posibles candidatos para una celda
void posiblesValores(const tSudoku sudoku, int fila, int columna, tCandidatos& posibles);

//comprueba si es posible colocar un valor en una celda
//@valor, el valor, tsudoku struct con el sudoku, tCandidatos, array con posibles valores para una celda
bool buscaSiEsPosible(int valor, tSudoku& sudoku, tCandidatos& posibles);

//opcion 1, ver posibles valores para una celda
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion1 (const tSudoku sudoku);

//opcion 2, colocar un valor en una casilla
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion2 (tSudoku& sudoku);

//opcion 3, borra el valor de una casilla
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion3 (tSudoku& sudoku);

//opcion 4, muestra los valores incorrectos
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion4 (const tSudoku sudoku, const tIntTablero solucion);

//opcion 5, inicializa el sudoku al valor inicial
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion5 (tSudoku& sudoku);

//opcion 6, completa las casillas que solo puedan tener un valor
//@tSudoku sudoku, struct que tiene el sudoku original, contador y array booleano 
void opcion6 (tSudoku& sudoku);

//funcion para copiar un array a otro
//@tSudoku sudoku, tiene el sudoku original
//@tSudoku copia, aqui se guarda el sudoku original
void copia_arrays (const tSudoku sudoku, tSudoku& copia);


///////////////////////////////////////////////////////////

//funciones 

void limpiar(){
    cin.sync();
    cin.clear();
}

int mostrarMenu(){
    char c;
    int opcion;
    cout << "0.- SALIR\n";
    cout << "1.- Ver posibles valores de casilla\n";
    cout << "2.- Colocar un valor en una casilla\n";
    cout << "3.- Borrar el valor de una casilla\n";
    cout << "4.- Mostrar valores incorrectos\n";
    cout << "5.- Reiniciar tablero\n";
    cout << "6.- Completar casillas simples\n";
    cout << "Opcion: ";
    c = cin.peek();
	//si la opcion introducida por el usuario no es un digito, retorna un 7 ya que es una opcion no valida
	//que se procesara como tal en el main
    if (!isdigit(c)) opcion = 7;
	else cin >> opcion;
    return opcion;
}

void MostrarSudoku (const tSudoku sudoku){
    cout << '\n' << setfill('-') << setw(31) << '-' << endl;
    for (int fila = 0; fila < DIM; fila++){
        for (int columna = 0; columna < DIM; columna++){
			//hay que mostrar una barra vertical cada tres posiciones para delimitar regiones
            if (columna % 3 == 0) cout << '|';
            if (sudoku.Tablero[fila][columna] == 0) cout << "   ";
            else cout << " " << sudoku.Tablero[fila][columna] << " ";
        }cout << '|' << endl;
		//para delimitar las regiones, hay que mostrar una linea de guiones
        if ((fila+1) % 3 == 0) cout << setfill('-') << setw(31) << '-' << endl;
    }
}

void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion){
    string default_sudoku = "sudoku1.txt", default_solucion = "solsdk1.txt", nombreArchivo;
    char c;
    bool is_open_sudFile = false, is_open_sol = false;
    while (!is_open_sudFile){
        cout << "Nombre del Sudoku (Intro -> archivo por defecto 'sudoku.txt'): ";
        limpiar();
        c = cin.peek();
		//si se pulsa enter, se usa el nombre por defecto
        if (c == '\n') nombreArchivo = default_sudoku;
        else cin >> nombreArchivo;
        fSudoku.open(nombreArchivo);
		//si hay error al abrir el archivo, se pondra el booleano a falso y se continuara ejecutando el bucle
		is_open_sudFile = fSudoku.is_open();
	}while (!is_open_sol){
		cout << "Nombre de la solucion (Intro -> archivo por defecto 'solsdk1.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_solucion;
        else cin >> nombreArchivo;
        fSolucion.open(nombreArchivo);
        is_open_sol = fSolucion.is_open();
    }

}

void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, tIntTablero& solucion, bool& error){
    int contador = 0, numerito, fila, columna;
    error = false;
    sudoku.contador = 0;
    for (int i = 0; i < 9; i++){//se inicializan el tablero booleano y el tablero con el sudoku a 0
        for (int j = 0; j < 9; j++){
            sudoku.boolTablero[i][j] = false;
            sudoku.Tablero[i][j] = 0;
        }
    }
    for (int fila = 0; fila < 9; fila++){//se rellena el tablero con la solucion, leyendo el archivo original
        for ( int columna = 0; columna < 9; columna ++, contador++){
            fSolucion >> numerito;
            solucion[fila][columna] = numerito;
        }
    }fSudoku >> fila;//igual con el archivo que contiene el sudoku original
    while((!error) && (fila > 0)){
        fSudoku >> columna;
        fSudoku >> numerito;
        sudoku.contador++;
        error = (sudoku.contador > 81)||(numerito > 9) || (numerito < 1);//casos que daran error
        if (!error){
			sudoku.Tablero[fila-1][columna-1] = numerito;//inicializacion del tablero del sudoku
			sudoku.boolTablero[fila-1][columna-1] = true;//se pone true en las que sean posiciones iniciales
		}
		fSudoku >> fila;
	}
}

int comprobarNumero(){
	int num;
	cin >> num;
	while ((num <= 0) || (num > 9) || cin.fail()){//casos no validos
		limpiar();
		cout << "Error, introduzca el numero de nuevo: "; 
		cin >> num;
	}
	num -= 1;//se resta uno ya que el usuario debe elegir un numero entre  1 y DIM y el programa trabaja con indices del 0 al DIM - 1
	return num;
}

void inicializarCandidatos(tCandidatos& posibles){
	//Inicializa el array de candidatos a 0 y pone el contador a 0
	posibles.contador = 0;
	for (int i = 0; i< DIM; i++){
		posibles.lista[i] = 0;
	}
}

//busqueda por filas
bool estaEnFila (const tSudoku sudoku, int fila, int columnaOriginal, int num){
	bool encontrado = false;
	int columna = 0;
	while((columna < (DIM)) && !encontrado){
		if ((sudoku.Tablero[fila][columna] == num)&&(columna != columnaOriginal))  encontrado = true;
		else columna++;
	}
	return encontrado;
}
//busqueda por columnas
bool estaEnColumna (const tSudoku sudoku, int columna, int filaOriginal, int num){
	bool encontrado = false;
	int fila = 0;
	while((fila < (DIM)) && !encontrado){
		if ((sudoku.Tablero[fila][columna] == num)&&(fila != filaOriginal))encontrado = true;
		else fila++;  
	}
	return encontrado;
}

//busca en una fila de una region
bool estaEnRegionPorFilas(const tSudoku sudoku, int num, int inicioColumna, int columnaOriginal, int filaOriginal, int fila){
	int columna = inicioColumna;
	bool encontrado = false;
	while((columna < (inicioColumna + RAIZ_DIM)) && (!encontrado)){
			if ((sudoku.Tablero[fila][columna] == num)&&((fila != filaOriginal) || (columna != columnaOriginal))) encontrado = true;
			else columna++;  
		}
	return encontrado;
}

//busca en una region
bool estaEnRegion (const tSudoku sudoku, int filaOriginal, int columnaOriginal, int num){
	bool encontrado = false;
	int inicioFila = (filaOriginal/3)*3, inicioColumna = (columnaOriginal/3)*3;
	int fila = inicioFila, columna = inicioColumna;
	while((fila < inicioFila + RAIZ_DIM) && !encontrado){
		encontrado = estaEnRegionPorFilas(sudoku, num, inicioColumna, columnaOriginal, filaOriginal, fila);
		fila++;
	}
	return encontrado;
}

void posiblesValores (const tSudoku sudoku, int fila, int columna, tCandidatos& posibles){  
	bool bFila, bColumna, bRegion;
	for (int i = 1; i <= DIM; i++){//prueba con numeros del 1 al 9
		bRegion = estaEnRegion (sudoku, fila, columna, i);
		bColumna = estaEnColumna(sudoku, columna, fila, i);
		bFila = estaEnFila(sudoku, fila, columna, i);
		//si el numero no esta en la region NI en la fila NI en la columna, entonces es un posible candidato
		if (!((bFila)||(bColumna)||(bRegion))){
			posibles.lista[posibles.contador] = i;
			posibles.contador++;
		}
	}
}

void opcion1 (const tSudoku sudoku){
	int fila, columna;
	tCandidatos posibles;
	inicializarCandidatos(posibles);
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); 
	columna = comprobarNumero();
	//caso en el que la casilla introducida no está vacía
	if (sudoku.Tablero[fila][columna] != 0) cout << "CASILLA NO VACIA\n";
	else{
		//si la casilla esta vacía, comprueba los posibles valores para esa casilla
		posiblesValores(sudoku, fila, columna, posibles);
		cout << "Los posibles valores para la casilla (" << fila +1 << ", " << columna +1 << ") son: ";
		for (int j = 0; j < posibles.contador; j++){
			cout << posibles.lista[j] << " ";
		}
		cout << "\n";
	}
}

bool buscaSiEsPosible(int valor, tSudoku& sudoku, tCandidatos& posibles){
	int i = 0;
	bool encontrado = false;
	//comprobará que el valor introducido por el usuario no coincida con ninguno en la misma region, col., o fila
	//lo hara buscando el valor por el array de candidatos
	while ((i < posibles.contador) && !encontrado){
		//en el momento en el que se encuentre, saldrá del bucle poniendo encontrado a true
		encontrado = (valor == posibles.lista[i]);
		i++;
	}//si no se encuentra, encontrado seguira estando a false
	return encontrado;
}

void opcion2 (tSudoku& sudoku){
	int fila, columna, valor;
	bool es_posible;
	tCandidatos posibles;
	inicializarCandidatos(posibles);
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); 
	columna = comprobarNumero();
	cout << "Introduzca el valor que desea colocar: ";
	valor = comprobarNumero();
	valor += 1; // la funcion comprobarNumero resta 1 automaticamente para que las filas y columnas comiencen con 0 en los arrays
	if (sudoku.boolTablero[fila][columna]) cout << "NO MODIFICABLE\n";
	else{
		if (sudoku.Tablero[fila][columna] != 0) cout << "CASILLA NO VACIA\n";
		else {
			posiblesValores(sudoku, fila, columna, posibles);
			es_posible = buscaSiEsPosible(valor, sudoku, posibles);
			if (es_posible){//si el valor es posible
				sudoku.Tablero[fila][columna] = valor;//se coloca en el sudoku
				sudoku.contador++;//y se aumenta el contador que indica el numero de casillas rellenas
			}else cout << "DIGITO NO VALIDO\n";//si el valor coincide con una columna o region o fila (es decir, !es_posible)
		}
	}
}

void opcion3 (tSudoku& sudoku){
	int fila, columna;
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); 
	columna = comprobarNumero();
	//caso en el que el la celda elegida por el usuario sea una celda original
	if (sudoku.boolTablero[fila][columna]) cout << "NO MODIFICABLE\n"; 
	else{
		//caso en el que la casilla ya estuviera vacía
		if (sudoku.Tablero[fila][columna] == 0) cout << "CASILLA VACIA\n";
		//caso valido
		else {
			sudoku.Tablero[fila][columna] = 0;
			sudoku.contador--;
		}
	}
}

void opcion4 (const tSudoku sudoku, const tIntTablero solucion){
	int fila = 0, columna = 0;
	bool hayErrores = false;
	cout << "Errores:\n";
	for (int i = 0; i < DIM; i++){ 
		for (int j = 0; j < DIM; j++){
			if ((sudoku.Tablero[i][j] != 0) && (sudoku.Tablero[i][j] != solucion[i][j])){
				cout << "[" << i+1 << "," << j+1 << "] (" << sudoku.Tablero[i][j] << ")" << endl;
				hayErrores = true;//una vez que hayErrores se haya puesto a true, no cambiara
			}
		}
	}if (!hayErrores) cout << "NO HAY NINGUN ERROR.\n";
}

void opcion5 (tSudoku& sudoku){
	//reinicia el tablero
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
			if (!sudoku.boolTablero[i][j]){
				//si la casilla fuera originalmente 0, no haria falta borrarla ni decrementar el contador
				if (sudoku.Tablero[i][j] != 0){
					sudoku.Tablero[i][j] = 0;
					sudoku.contador--;
				}
			}
		}
    }
}

void copia_arrays (const tSudoku sudoku, tSudoku& copia){
	for (int i = 0; i< DIM; i++){
		for (int j = 0; j< DIM; j++){
			copia.Tablero[i][j] = sudoku.Tablero[i][j];
		}
	}
}

void opcion6 (tSudoku& sudoku){
	tSudoku copia;
	copia_arrays (sudoku, copia);
	tCandidatos posibles;
	int diferencia = sudoku.contador;
	inicializarCandidatos(posibles);
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			if (sudoku.Tablero[i][j] == 0){
				posiblesValores(copia, i, j, posibles);
				if (posibles.contador == 1){
					sudoku.Tablero[i][j] = posibles.lista[0];
					sudoku.contador++;
				}
				inicializarCandidatos(posibles);
			}
		}
	}diferencia = sudoku.contador - diferencia;
	if (diferencia != 0) cout << "Se han completado " << diferencia << " celdas.\n";
	else cout << "No se ha podido completar ninguna celda.\n";
}


///////////////////////////////////////////////////////////

int main(){	
	char c;
    tSudoku sudo;
    tIntTablero solucion;
    ifstream fInSudoku, fInSolucion;
    int opcion = 1;
    bool fin = false;
    abrirArchivos(fInSudoku, fInSolucion);
    inicializarTableros(fInSudoku, fInSolucion, sudo, solucion, fin);
	//al ejecutar la funcion inicializarTableros, fin se pondra a true cuando haya algun error en los archivos originales
	//y de esta manera no entrara en el bucle
    if (fin) cout << "ERROR, el sudoku inicial contiene errores.\n";
	else MostrarSudoku(sudo);
	while (!fin){
        limpiar();
        opcion = mostrarMenu();
		limpiar();
		if		(opcion == 0) fin = true;
		else if (opcion == 1) opcion1(sudo);
		else if (opcion == 2) opcion2(sudo);
		else if (opcion == 3) opcion3(sudo);
		else if (opcion == 4) opcion4(sudo, solucion);
		else if (opcion == 5) opcion5(sudo);
		else if (opcion == 6) opcion6(sudo);
		else cout << "Opcion no valida! Introduzcala de nuevo: ";
		if(!fin) MostrarSudoku(sudo);
		cout << sudo.contador << endl;
		if (sudo.contador == 81){//si el contador llega a ser 81, quiere decir que el sudoku estara acabado
			cout << "\nENHORABUENA HAS TERMINADO EL SUDOKU!!!!!!!!\n" << "Pulsa intro para acabar: ";
			cin.get(c);
			fin = true; //se pondra fin a true, y asi no se volvera a ejecutar el bucle
		}
    }
}
























/*#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int DIM = 9;


typedef int tIntTablero[DIM][DIM];
typedef bool tBoolTablero[DIM][DIM];
typedef int tIntCandidatos[DIM];

typedef struct{
    int contador;
    tIntTablero Tablero;
    tBoolTablero boolTablero;
}tSudoku;
typedef struct{
	int contador;
	tIntCandidatos lista;
}tCandidatos;

//function prototype
void limpiar(); //limpiar
int mostrarMenu (); // muestra el menu
void MostrarSudoku (const tSudoku sudoku);//mostrar sudoku por pantalla 
void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion); //abrir archivos
void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, tIntTablero& solucion, bool& error);
int comprobarNumero();
void inicializarCandidatos(tCandidatos& posibles);
int unicoCandidato(const tCandidatos posibles);
void posiblesValores(const tSudoku sudoku, int fila, int columna, tCandidatos& posibles);
bool buscaSiEsPosible(int valor, tSudoku& sudoku, tCandidatos& posibles);
void opcion1 (const tSudoku sudoku);
void opcion2 (tSudoku& sudoku);
void opcion3 (tSudoku& sudoku);
void opcion4 (const tSudoku sudoku, const tIntTablero solucion);
void opcion5 (tSudoku& sudoku);
void opcion6 (tSudoku& sudoku);
void VerValores (const tSudoku sudoku, bool mostrarPorPantalla, int fila, int columna); //opcion 1, ver valores posibles

//funciones 
void limpiar(){
    cin.sync();
    cin.clear();
}
int mostrarMenu(){
    char c;
    int opcion;
    cout << "0.- SALIR\n";
    cout << "1.- Ver posibles valores de casilla\n";
    cout << "2.- Colocar un valor en una casilla\n";
    cout << "3.- Borrar el valor de una casilla\n";
    cout << "4.- Mostrar valores incorrectos\n";
    cout << "5.- Reiniciar tablero\n";
    cout << "6.- Completar casillas simples\n";
    cout << "7.- Resolutor\n";
    cout << "Opcion: ";
    c = cin.peek();
    if (!isdigit(c)) opcion = 7;
    else cin >> opcion;
    return opcion;
}
void MostrarSudoku (const tSudoku sudoku){
    cout << '\n' << setfill('-') << setw(31) << '-' << endl;
    for (int fila = 0; fila < DIM; fila++){
        for (int columna = 0; columna < DIM; columna++){
            if (columna % 3 == 0) cout << '|';
            if (sudoku.Tablero[fila][columna] == 0) cout << "   ";
            else cout << " " << sudoku.Tablero[fila][columna] << " ";
        }cout << '|' << endl;
        if ((fila+1) % 3 == 0) cout << setfill('-') << setw(31) << '-' << endl;
    }
}

void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion){
    string default_sudoku = "sudoku1.txt", default_solucion = "solsdk1.txt", nombreArchivo;
    char c;
    bool is_open_sudFile = false, is_open_sol = false;
    while (!is_open_sudFile){
        cout << "Nombre del Sudoku (Intro -> archivo por defecto 'sudoku.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_sudoku;
        else cin >> nombreArchivo;
        fSudoku.open(nombreArchivo);
		is_open_sudFile = fSudoku.is_open();
	}while (!is_open_sol){
        cout << "Nombre de la solucion (Intro -> archivo por defecto 'solsdk1.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_solucion;
        else cin >> nombreArchivo;
        fSolucion.open(nombreArchivo);
        is_open_sol = fSolucion.is_open();
    }

}

void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, tIntTablero& solucion, bool& error){
    int contador = 0, numerito, fila, columna;
    error = false;
    sudoku.contador = 0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            sudoku.boolTablero[i][j] = false;
            sudoku.Tablero[i][j] = 0;
        }
    }
    for (int fila = 0; fila < 9; fila++){
        for ( int columna = 0; columna < 9; columna ++, contador++){
            fSolucion >> numerito;
            solucion[fila][columna] = numerito;
        }
    }fSudoku >> fila;
    while((!error) && (fila > 0)){
        fSudoku >> columna;
        fSudoku >> numerito;
        sudoku.contador++;
        error = (sudoku.contador > 81)||(numerito > 9) || (numerito < 1);
        if (!error){
			sudoku.Tablero[fila-1][columna-1] = numerito;
			sudoku.boolTablero[fila-1][columna-1] = true;
		}
        fSudoku >> fila;
    }
}
int comprobarNumero(){
	int num;
	cin >> num;
	while ((num <= 0) || (num > 9) || cin.fail()){
		limpiar();
		cout << "Error, introduzca el numero de nuevo: "; 
		cin >> num;
	}
	num -= 1;
	return num;
}
/*void inicializarCandidatos(tCandidatos& posibles){
	posibles.contador = DIM;
	for (int i = 0; i< DIM; i++){
		posibles.lista[i] = i+1;
	}
}//////////////////////

void inicializarCandidatos(tCandidatos& posibles){
	posibles.contador = 0;
	for (int i = 0; i< DIM; i++){
		posibles.lista[i] = 0;
	}
}
int unicoCandidato(const tCandidatos posibles){
	int pos = 0, unico;
	bool encontrado = false;
	while ((pos < DIM) && !encontrado){
		if (posibles.lista[pos] != 0){
			encontrado = true;
			unico = posibles.lista[pos];
		}else pos++;
	}
	return unico;
}
bool estaEnFila (const tSudoku sudoku, int fila, int columnaOriginal, int num){
	bool encontrado = false;
	int columna = 0;
	while((columna < (DIM)) && !encontrado){
		if ((sudoku.Tablero[fila][columna] == num) && (columna != columnaOriginal))  encontrado = true;
		 else columna++;  
	}
	return encontrado;
}
bool estaEnColumna (const tSudoku sudoku, int columna, int filaOriginal, int num){
	bool encontrado = false;
	int fila = 0;
	while((fila < (DIM)) && !encontrado){
		if ((sudoku.Tablero[fila][columna] == num) && (fila != filaOriginal))encontrado = true;
		 else fila++;  
	}
	return encontrado;
}
bool estaEnRegion (const tSudoku sudoku, int filaOriginal, int columnaOriginal, int num){
	bool encontrado = false;
	int inicioFila = (filaOriginal/3)*3, inicioColumna = (columnaOriginal/3)*3;
	int fila = inicioFila, columna = inicioColumna;
	while((fila <= inicioFila + 2) && !encontrado){
		while((columna <= inicioColumna + 2) && !encontrado){
			if ((sudoku.Tablero[fila][columna] == num) && ((fila != filaOriginal) || (columna != columnaOriginal))) encontrado = true;
			else columna++;  
		}
		columna = inicioColumna;
		fila++;  
	}
	return encontrado;
}
/*void posiblesValores (const tSudoku sudoku, int fila, int columna, tCandidatos& posibles){  
	bool bfila, bcolumna, bregion;
	for (int i = 1; i <= DIM; i++){
		bregion = estaEnRegion (sudoku, fila, columna, i);
		bcolumna = estaEnColumna(sudoku, columna, fila, i);
		bfila = estaEnFila(sudoku, fila, columna, i);
		if ((bfila== true) || (bcolumna == true) || (bregion == true)){
			posibles.lista[i-1] = 0;
			posibles.contador--;
		}
	}
}/////////////////////////////////////////

void posiblesValores (const tSudoku sudoku, int fila, int columna, tCandidatos& posibles){  
	bool bFila, bColumna, bRegion;
	for (int i = 1; i <= DIM; i++){
		bRegion = estaEnRegion (sudoku, fila, columna, i);
		bColumna = estaEnColumna(sudoku, columna, fila, i);
		bFila = estaEnFila(sudoku, fila, columna, i);
		if (!((bFila)||(bColumna)||(bRegion))){
			posibles.lista[posibles.contador] = i;
			posibles.contador++;
		}
	}
}
void opcion1 (const tSudoku sudoku){
	int fila, columna;
	tCandidatos posibles;
	inicializarCandidatos(posibles);
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); columna = comprobarNumero();
	//cout << "Introduzca la fila: ";
	//fila = comprobarNumero();
	//cout << "Introduzca la columna: ";
	//columna = comprobarNumero();
	if (sudoku.Tablero[fila][columna] != 0) cout << "CASILLA NO VACIA\n";
	else{
		posiblesValores(sudoku, fila, columna, posibles);
		cout << "Los posibles valores para la casilla (" << fila +1 << ", " << columna +1 << ") son: ";
		for (int j = 0; j < posibles.contador; j++){
			cout << posibles.lista[j] << " ";
		}
		cout << "\n";
	}
}
bool buscaSiEsPosible(int valor, tSudoku& sudoku, tCandidatos& posibles){
	int i = 0;
	bool encontrado = false;
	while ((i < posibles.contador) && !encontrado){
		encontrado = (valor == posibles.lista[i]);
		i++;
	}return encontrado;
}
void opcion2 (tSudoku& sudoku){
	int fila, columna, valor;
	tCandidatos posibles;
	inicializarCandidatos(posibles);
	//cout << "Introduzca la fila y : ";
	//fila = comprobarNumero();
	//cout << "Introduzca la columna: ";
	//columna = comprobarNumero();
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); columna = comprobarNumero();
	cout << "Introduzca el valor que desea colocar: ";
	valor = comprobarNumero();
	valor += 1; // la funcion comprobarNumero resta 1 automaticamente para que las filas y columnas comiencen con 0 en los arrays
	if (sudoku.boolTablero[fila][columna]) cout << "NO MODIFICABLE\n";
	else{
		if (sudoku.Tablero[fila][columna] != 0) cout << "CASILLA NO VACIA\n";
		else {
			posiblesValores(sudoku, fila, columna, posibles);
			/*if (posibles.lista[valor - 1] != 0){
				sudoku.Tablero[fila][columna] = valor;
				MostrarSudoku(sudoku);
				sudoku.contador++;
			}else cout << "DIGITO NO VALIDO\n";
		}/////////////////////////////////////////////
			if (buscaSiEsPosible(valor, sudoku, posibles)){//si el valor es posible
				sudoku.Tablero[fila][columna] = valor;
				sudoku.contador++;
				MostrarSudoku(sudoku);
			}else cout << "DIGITO NO VALIDO\n";//si el valor coincide con una columna o region o fila
		}
	}
}
void opcion3 (tSudoku& sudoku){
	int fila, columna/*, valor, posibles[DIM] = {1,2,3,4,5,6,7,8,9}////////////////////////////////;
	cout << "Introduce fila y columna [1..9]: ";
	fila = comprobarNumero(); columna = comprobarNumero();
	/*valor = comprobarNumero();
	valor += 1; // la funcion comprobarNumero resta 1 automaticamente para que las filas y columnas comiencen con 0 en los arrays
	///////////////////////////////////////////////////
	if (sudoku.boolTablero[fila][columna]) cout << "NO MODIFICABLE\n";
	else{
		if (sudoku.Tablero[fila][columna] == 0) cout << "CASILLA VACIA\n";
		else {
				sudoku.Tablero[fila][columna] = 0;
				MostrarSudoku(sudoku);
		}
	}
}
void opcion4 (const tSudoku sudoku, const tIntTablero solucion){
	int fila = 0, columna = 0, contador = 0;
	bool error = false;
	/*while((fila < DIM) && !error){					//primero realizamos una busqueda para ver si hay errores...
		while((columna < DIM) && !error){
			if ((sudoku.Tablero[fila][columna] != 0) && (sudoku.Tablero[fila][columna] != solucion[fila][columna])) error = true;
			columna++;  
		}
		fila++; 
	}//////////////////////////////////////////////////////////////////
	//if (error){
		cout << "Errores:\n";
		for (int i = 0; i < DIM; i++){					// y si los hay, un recorrido para mostrarlos
			for (int j = 0; j < DIM; j++){
				if ((sudoku.Tablero[i][j] != 0) && (sudoku.Tablero[i][j] != solucion[i][j])){
					cout << "[" << i+1 << "," << j+1 << "] (" << sudoku.Tablero[i][j] << ")";
					contador++;
				}
			}
		}if (contador == 0) cout << "NO HAY NINGUN ERROR.\n";
	//}else cout << "NO HAY ERRORES\n";
}
void opcion5 (tSudoku& sudoku){
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
			if (!sudoku.boolTablero[i][j]){
				sudoku.Tablero[i][j] = 0;
				sudoku.contador--;

			}
        }
    }
}
/*bool opcion6 (tSudoku& sudoku){
	tCandidatos posibles;
	bool cambio = false;
	int diferencia = sudoku.contador;
	inicializarCandidatos(posibles);
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			if (sudoku.Tablero[i][j] == 0){
				posiblesValores(sudoku, i, j, posibles);
				if (posibles.contador == 1){
					sudoku.Tablero[i][j] = posibles.lista[0];//unicoCandidato(posibles);
					sudoku.contador++;
					cambio = true;
				}
				inicializarCandidatos(posibles);
			}
		}
	}diferencia = sudoku.contador - diferencia;
	if (diferencia != 0) cout << "Se han completado " << diferencia << " celdas.\n";
	return cambio;
}/////////////////////////////////////////////////////////////////////////
void opcion6 (tSudoku& sudoku){
	tSudoku copia = sudoku;
	tCandidatos posibles;
	int diferencia = sudoku.contador;
	inicializarCandidatos(posibles);
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			if (sudoku.Tablero[i][j] == 0){
				posiblesValores(copia, i, j, posibles);
				if (posibles.contador == 1){
					sudoku.Tablero[i][j] = posibles.lista[0];
					sudoku.contador++;
				}
				inicializarCandidatos(posibles);
			}
		}
	}diferencia = sudoku.contador - diferencia;
	if (diferencia != 0) cout << "Se han completado " << diferencia << " celdas.\n";
}

int main(){
	char c;
    tSudoku sudo;
    tIntTablero solucion;
    ifstream fInSudoku, fInSolucion;
    int opcion = 1;
    bool fin = false;
    abrirArchivos(fInSudoku, fInSolucion);
    inicializarTableros(fInSudoku, fInSolucion, sudo, solucion, fin);
    if (fin) cout << "ERROR, el sudoku inicial contiene errores.\n";
  	MostrarSudoku(sudo);
	while (!fin){

        limpiar();
        opcion = mostrarMenu();
		limpiar();
		if (opcion == 0) fin = true;
		else if (opcion == 1) opcion1(sudo);
		else if (opcion == 2) opcion2(sudo);
		else if (opcion == 3) opcion3(sudo);
		else if (opcion == 4) opcion4(sudo, solucion);
		else if (opcion == 5) opcion5(sudo);
		else if (opcion == 6) opcion6(sudo);
		else cout << "Opcion no valida! Introduzcala de nuevo: ";
		MostrarSudoku(sudo);
		if (sudo.contador == 81){
			cout << "\nENHORABUENA HAS TERMINADO EL SUDOKU!!!!!!!!\n" << "Pulsa intro para acabar: ";
			cin.get(c);
			fin = true;
		}
    }
}*/