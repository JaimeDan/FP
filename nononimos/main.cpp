/*  Practica 3 opcional, sudokus irregulares
 *	Practica realizada por: Jesús Aguirre Pemán y Jaime-Dan Porras Rhee
 *	En la practica el usuario puede manejar un sudoku irregular que se muestra por la ventana grafica.
 *	El usuario puede:
 *		ver los posibles valores para una casilla, rellenar una casilla, borrar el valor de una casilla (no inicial),
 *		mostrar los valores incorrectos, reiniciar el tablero y completar las casillas que solo tengan un candidato posible.
 *	Por defecto se cargará el sudoku que aparece en el enunciado de la práctica, pero cambiando los archivos de entrada
 *		se puede manejar un sudoku de regiones irregulares sea cual sea.
 *	NOTA: los archivos que cargan el sudoku por defecto tienen por nombre: 
 *		"sudokunononimos.txt" para el sudoku inicial, "solsdknononimos.txt" para la solucion y "regnononimos.txt" para el mapa de regiones
 */


#include <iostream>	
#include <fstream>
#include <string>
#include <sstream>		
#include <cstring>
#include <iomanip>
using namespace std; // prefijo de la STL
#include "ventanaGrafica.h"	// ventana grafica

const int DIM = 9;				//numero de filas y columnas
const int MED_CELDA = 10;		//ancho y alto de una celda en la ventana grafica

typedef int tIntTablero[DIM][DIM];		//tablero 9x9 que guarda enteros
typedef bool tBoolTablero[DIM][DIM];	//tablero 9x9 que guarda booleanos
typedef int tIntCandidatos[DIM];		//array de 9 casillas que guarda los posibles candidatos para una celda

typedef struct{//estructura usada por tArrayCoordenadas, guarda la coordenada x y la coordenada y de una posicion
	double x;
	double y;
}tCoordenada;

typedef tCoordenada tArrayCoordenadas[DIM][DIM];//guarda la coordenada x e y de una celda, para la ventana gráfica
												//tambien guarda la fila y columna de una determinada casilla que pertenece a una region
												//mientras que las filas representan regiones, las columnas son celdas pertenecientes
												//a dicha region, en las que se guarda el numero de fila y columna de la celda

typedef struct{
    int contador;							//contador que indica cuantas casillas estan rellenas
    tIntTablero Tablero;					//tablero con el sudoku inicial, que el usuario puede ir completando
	tIntTablero Regiones;					//array con el mapa de regiones
	tIntTablero Solucion;					//tablero con la solucion
    tBoolTablero boolTablero;				//tablero booleano que indica cuales casillas son las iniciales
	tArrayCoordenadas coordRegiones;		//array que por cada region (del 1 al 9) indica que casillas pertenecen a dicha region, 
													//guardando la fila y columna de cada casilla
	tArrayCoordenadas Coordenadas;			//array que guarda las coordenadas (de la esquina superior izquierda) de cada celda
													//para la ventana grafica
}tSudoku;


typedef struct{								//struct con un array que guarda los posibles candidatos para una celda, y un contador
	int contador;							//que indica cuantas celdas del array se han rellenado
	tIntCandidatos lista;
}tCandidatos;




///////////////////////////////////////////////////////////



//function prototype

//limpiar, limpia el buffer y el flag de error
void limpiar();

// muestra el menu, retorna la opcion elegida
int mostrarMenu ();

//abrir archivos
//@ifstream fSudoku, flujo para leer el archivo con el sudoku original
//@ifstream fSolucion, flujo para leer el archivo con la solucion del sudoku
void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion);

//inicializa tableros
//@fSudoku, para el archivo con el sudoku inicial, @fSolucion para el archivo con la solucion
//@tSudoku, struct con el sudoku, @tIntTablero, array bidimensional con la solucion
//@bool error indica si el archivo con el sudoku inicial contiene errores
void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, bool& error);

//valida el numero introducido por teclado por el usuario
int comprobarNumero();

//inicializa la lista de candidatos a 0 y el contador que indica posicion a 0
//@tCandidatos, array con los candidatos
void inicializarCandidatos(tCandidatos& posibles);

//mira los posibles valores para una celda
//@tSudoku, struct con el sudoku
//@int fila y columna, valores de entrada, tCandidatos posibles, array con posibles candidatos para una celda
void posiblesValores (const tSudoku sudoku, int fila, int columna, tCandidatos& posibles);

//comprueba si es posible colocar un valor en una celda
//@valor, el valor, tsudoku struct con el sudoku, tCandidatos, array con posibles valores para una celda
bool buscaSiEsPosible(int valor, tCandidatos& posibles);

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
//@tIntTablero copia, aqui se guarda el sudoku original
//Se tiene que sobrecargar la funcion posibles valores para que la opcion 6 funcione correctamente
void copia_arrays (const tSudoku sudoku, tIntTablero& copia);

//dibujar tablero
//dibuja el tablero en la ventana gráfica
//@tSudoku sudoku: estructura que tiene el mapa de regiones, necesario para dibujar el sudoku delimitando cada región
void dibujar_tablero (const tSudoku sudoku);

//dibuja el numero de fila y de columna al borde del tablero
void dibujar_fila_columna();

//inicializar coordenadas
//inicializa las coordenadas de cada celda
//@tArrayCoordenadas Coordenadas, es el array que tiene las coordenadas de cada celda
void inicializarCoordenadas(tArrayCoordenadas& Coordenadas);

//dibujar numeros iniciales
//dibuja los numeros del sudoku inicial
//@tSudoku sudoku array que tiene el sudoku inicial, coordenadas de cada celda, etc
void dibujar_sudoku_inicial (const tSudoku sudoku);

//funcion que dibujara el sudoku inicial y el numero de cada fila y columna, llamando al resto de las funciones
//@tSudoku sudoku, estructura con el sudoku inicial, mapa de regiones, etc
void dibuja_todo(const tSudoku sudoku);

//dibuja un numero en su celda
//@tArrayCoordenadas, array que contiene las coordenadas de cada celda
//@int fila, fila en la que está el número
//@int columna, columna en la que está el número
//@int valor, valor que se quiere colocar en la celda
void dibuja_numero (const tArrayCoordenadas, int fila, int columna, int valor);

//inicializa el tablero que dice a qué región pertenece cada casilla
//también se hace un array en el que por cada región se guarda otro array con las casillas que pertenecen a dicha región
//@tSudoku sudoku, estructura que contiene el array con el "mapa" de regiones y el array que tiene otro array por cada región
//@ifstream fRegiones, para el archivo que tiene el "mapa" de regiones
void inicializa_regiones(tSudoku& sudoku, ifstream& fRegiones);

//pasa de int a string
//@int d, numero que se desea pasar a string (para poder ser mostrado en la ventana grafica)
string intToStr(int d);



////////////////////////////////////////////////////////////////////////////



//funciones 
void limpiar(){
    cin.sync();
    cin.clear();
}

int mostrarMenu(){
    char c;
    int opcion;
    cout << "\n0.- SALIR\n";
    cout << "1.- Ver posibles valores de casilla\n";
    cout << "2.- Colocar un valor en una casilla\n";
    cout << "3.- Borrar el valor de una casilla\n";
    cout << "4.- Mostrar valores incorrectos\n";
    cout << "5.- Reiniciar tablero\n";
    cout << "6.- Completar casillas simples\n";
    cout << "Opcion: ";
    c = cin.peek();
	//si la opcion introducida por el usuario no es un digito, retorna un 7 ya que es una opcion no valida
    if (!isdigit(c)) opcion = 7;
	else cin >> opcion;
    return opcion;
}

void inicializarCoordenadas(tSudoku& Coordenadas){
    double xIni = -37.5, yIni = 34.5;
    double auxY = yIni, auxX;
    for (int i = 0; i < DIM; i++){//no se si se puede con for
        auxX = xIni;
        for (int j = 0; j < DIM; j++){
            Coordenadas.Coordenadas[i][j].x = auxX;
            Coordenadas.Coordenadas[i][j].y = auxY;
            auxX += MED_CELDA;        
        }
        auxY -= MED_CELDA;
    }
}
void inicializa_regiones(tSudoku& sudoku, ifstream& fRegiones){
	int region;
	tIntCandidatos contador = {0,0,0,0,0,0,0,0,0};//es un contador que por cada región indica cuantas celdas se han rellenado
	for (int fila = 0; fila < DIM; fila++){
		for (int columna = 0; columna < DIM; columna++){
			fRegiones >> region;
			sudoku.Regiones[fila][columna] = region;
			sudoku.coordRegiones[region][contador[region]].x = fila;	//para la region que haya tocado, se guarda en la 
																		//primera columna vacía (indicada por el contador) la coordenada x
			sudoku.coordRegiones[region][contador[region]].y = columna;	//lo mismo para la coordenada y
			contador[region]++; //se incrementa el contador de la región para indicar que una columna ha sido ocupada
		}
	}
}
string intToStr(int d){ //pasa de int a string
	stringstream out;
	out << d;
	return out.str();
}

void dibuja_todo(const tSudoku sudoku){
	dibujar_tablero (sudoku);
	dibujar_fila_columna ();
	dibujar_sudoku_inicial (sudoku);
}

void dibujar_tablero(const tSudoku sudoku){
	double x_0, y_0, x_1, y_1, x0_ini = -41, x1_ini = 49, y0_ini = 41, y1_ini = -49;
	double desajuste_x = 3.5, desajuste_y = 6.5;
	for (int fila = 0; fila < DIM; fila++){
		for (int columna = 0; columna < DIM; columna++){
			x_0 = sudoku.Coordenadas[fila][columna].x - desajuste_x;
			y_0 = sudoku.Coordenadas[fila][columna].y + desajuste_y - MED_CELDA;
			//si la region de la celda i, j es distinta de la region de la celda de abajo, dibuja el borde de azul
            // se hace j+1 % DIM para que al llegar al final de la columna remarque el borde del tablero
            if (sudoku.Regiones[fila][columna] != sudoku.Regiones[(fila+1) % DIM][columna]){ // (para marcar la frontera de dos regiones)
                vgColor(VGAzul);
				vgLine(x_0, y_0, x_0 + MED_CELDA, y_0);
            }else { //si estan en la misma región
                vgColor(VGVerde);
				vgLine(x_0, y_0, x_0 + MED_CELDA, y_0);
			}
            //si la región de una celda es distinta a la región de la celda de la derecha, se pinta el borde de azul
            // se hace i+1 % DIM para que al llegar al final de la fila remarque el borde del tablero
            if (sudoku.Regiones[fila][columna] != sudoku.Regiones[fila][(columna+1) % DIM]){ // (para marcar la frontera de dos regiones)
                vgColor(VGAzul);
				vgLine(x_0 + MED_CELDA, y_0 + MED_CELDA, x_0 + MED_CELDA, y_0);
			}else{ //si estan en la misma región
                vgColor(VGVerde);
				vgLine(x_0 + MED_CELDA, y_0 + MED_CELDA, x_0 + MED_CELDA, y_0);
			}
        }
	}//aun quedan sin dibujar los bordes superior e izquierdo del tablero:
	vgColor(VGAzul);
    vgLine(x0_ini, y0_ini, x1_ini, y0_ini);                       //dibuja el borde superior
    vgLine(x0_ini, y0_ini, x0_ini, y1_ini);                       //dibuja el borde izquierdo
}

void dibujar_fila_columna(){
	vgColor(VGNegro);
	double x_ini = -47.5, y_ini = 45;
	string cad;
	for (int i=0; i<DIM; i++){
		cad = intToStr(i+1);
		vgCString(x_ini, y_ini - (MED_CELDA * (i+1)), cad.c_str());//dibuja el numero de fila
		vgCString(x_ini + (MED_CELDA * (i+1)), y_ini, cad.c_str());//dibuja el numero de columna
	}
}

void dibujar_sudoku_inicial(const tSudoku sudoku){
	double coordenada_x, coordenada_y;
	vgColor(VGNegro);
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			if (sudoku.Tablero[i][j] != 0){
				coordenada_x = sudoku.Coordenadas[i][j].x;		//guarda el valor de la coordenada x de la celda i, j
				coordenada_y = sudoku.Coordenadas[i][j].y;		//guarda el valor de la coordenada y de la celda i, j
				vgCString(coordenada_x, coordenada_y, intToStr(sudoku.Tablero[i][j]).c_str());	//dibuja el numero, convertido en cadena de caracteres, en su posicion
			}
		}
	}
}

void dibuja_numero (const tSudoku sudoku, int fila, int columna, int numero, VGColores color){
	vgColor(color);
	vgCString(sudoku.Coordenadas[fila][columna].x, sudoku.Coordenadas[fila][columna].y, intToStr(numero).c_str()); //dibuja el numero en su posicion
}

void abrirArchivos (ifstream& fSudoku, ifstream& fSolucion, ifstream& fRegiones){
    string default_sudoku = "sudokunononimos.txt", default_solucion = "solsdknononimos.txt", default_regiones = "regnononimos.txt", nombreArchivo;
    char c;
    bool is_open_sudFile = false, is_open_sol = false, is_open_regiones = false;
    while (!is_open_sudFile){//para el archivo con el sudoku inicial
        cout << "Nombre del Sudoku (Intro -> archivo por defecto 'sudokunononimos.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_sudoku; 		//si se pulsa enter, se usa el nombre por defecto
        else cin >> nombreArchivo;
        fSudoku.open(nombreArchivo);
		//si hay error al abrir el archivo, se pondrá el booleano a falso y se continuará ejecutando el bucle
		is_open_sudFile = fSudoku.is_open();
	}while (!is_open_sol){//para el archivo con la solucion
		cout << "Nombre de la solucion (Intro -> archivo por defecto 'solsdknononimos.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_solucion;
        else cin >> nombreArchivo;
        fSolucion.open(nombreArchivo);
        is_open_sol = fSolucion.is_open();
    }while (!is_open_regiones){//para el archivo con el mapa de regiones
		cout << "Nombre de la solucion (Intro -> archivo por defecto 'regnononimos.txt'): ";
        limpiar();
        c = cin.peek();
        if (c == '\n') nombreArchivo = default_regiones;
        else cin >> nombreArchivo;
        fRegiones.open(nombreArchivo);
        is_open_regiones = fRegiones.is_open();
    }
}


void inicializarTableros (ifstream& fSudoku, ifstream& fSolucion, tSudoku& sudoku, bool& error){
    int numero, fila, columna;
    error = false;
    sudoku.contador = 0;
    for (int i = 0; i < 9; i++){//se inicializan el tablero booleano y el tablero con el sudoku a 0
        for (int j = 0; j < DIM; j++){
            sudoku.boolTablero[i][j] = false;
            sudoku.Tablero[i][j] = 0;
        }
    }
    for (int fila = 0; fila < DIM; fila++){//se rellena el tablero con la solucion, leyendo el archivo original
        for ( int columna = 0; columna < DIM; columna ++){
            fSolucion >> numero;
			sudoku.Solucion[fila][columna] = numero;
        }
    }fSudoku >> fila;//igual con el archivo que contiene el sudoku original
    while((!error) && (fila > 0)){
        fSudoku >> columna;
        fSudoku >> numero;
        sudoku.contador++;
        error = (sudoku.contador > 81)||(numero > DIM) || (numero < 1);//casos que daran error
        if (!error){
			sudoku.Tablero[fila-1][columna-1] = numero;//inicializacion del tablero del sudoku, se resta uno ya que el array trabaja con indices del 0 al 8
			sudoku.boolTablero[fila-1][columna-1] = true;//se pone true en las que sean posiciones iniciales
		}
		fSudoku >> fila;
	}
}

int comprobarNumero(){
	int num;
	cin >> num;
	while ((num <= 0) || (num > DIM) || cin.fail()){//casos no validos
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
//busqueda en una region irregular
bool estaEnRegion (const tSudoku sudoku, int fila, int columna, int num){
	int region = sudoku.Regiones[fila][columna];
	int coordenada_x, coordenada_y;
	bool encontrado = false;
	int contador = 0;
	while ((contador<DIM) && (!encontrado)){
		coordenada_x = int(sudoku.coordRegiones[region][contador].x);		//se podria poner directamente sudoku.coordRegiones... 
		coordenada_y = int(sudoku.coordRegiones[region][contador].y);		//pero así queda más claro
		if (num == sudoku.Tablero[coordenada_x][coordenada_y]) encontrado = true;
		else contador++;
	}return encontrado;
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

bool buscaSiEsPosible(int valor, tCandidatos& posibles){
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
			es_posible = buscaSiEsPosible(valor, posibles);
			if (es_posible){//si el valor es posible
				sudoku.Tablero[fila][columna] = valor;//se coloca en el sudoku
				dibuja_numero(sudoku, fila, columna, valor, VGAzul);//dibuja el numero en azul para poder distinguirlo de un valor inicial
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
			dibuja_numero(sudoku, fila, columna, sudoku.Tablero[fila][columna], VGBlanco);
			sudoku.Tablero[fila][columna] = 0;
			sudoku.contador--;
		}
	}
}

void opcion4 (const tSudoku sudoku){
	//vgColor(VGRojo);
	bool hayErrores = false;
	cout << "Errores:\n";
	for (int fila = 0; fila < DIM; fila++){ 
		for (int columna = 0; columna < DIM; columna++){
			if ((sudoku.Tablero[fila][columna] != 0) && (sudoku.Tablero[fila][columna] != sudoku.Solucion[fila][columna])){
				cout << "[" << fila+1 << "," << columna+1 << "] (" << sudoku.Tablero[fila][columna] << ")" << endl;
				dibuja_numero(sudoku, fila, columna, sudoku.Tablero[fila][columna], VGRojo);//dibuja los numeros no correctos en rojo
				hayErrores = true;//una vez que hayErrores se haya puesto a true, no cambiara
			}
		}
	}if (!hayErrores) cout << "NO HAY NINGUN ERROR.\n";//si no hay ningun error, hayErrores permanecera en false y se mostrara el mensaje
}

void opcion5 (tSudoku& sudoku){
	//reinicia el tablero
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
			if (!sudoku.boolTablero[i][j]){
				//si la casilla fuera originalmente 0, no haria falta borrarla ni decrementar el contador
				if (sudoku.Tablero[i][j] != 0){
					dibuja_numero(sudoku, i, j, sudoku.Tablero[i][j], VGBlanco);
					sudoku.Tablero[i][j] = 0;
					sudoku.contador--;
				}
			}
		}
    }
}

void opcion6 (tSudoku& sudoku){
	tSudoku copia;
	copia = sudoku;//hay que copiar el struct entero para que funcionen correctamente las funciones de busqueda por fila, columna, etc
	int diferencia = sudoku.contador;
	tCandidatos posibles;
	inicializarCandidatos(posibles);
	for (int columna = 0; columna < DIM; columna++){
		for (int fila = 0; fila < DIM; fila++){
			if (sudoku.Tablero[fila][columna] == 0){
				posiblesValores(copia, fila, columna, posibles);
				if (posibles.contador == 1){
					sudoku.Tablero[fila][columna] = posibles.lista[0];
					dibuja_numero(sudoku, fila, columna, sudoku.Tablero[fila][columna], VGAzul);
					sudoku.contador++;
				}
				inicializarCandidatos(posibles);
			}
		}
	}
	diferencia = sudoku.contador - diferencia;
	if (diferencia != 0) cout << "Se han completado " << diferencia << " celdas.\n";
	else cout << "No se ha podido completar ninguna celda.\n";
}

//////////////////////////


int main() {
	vgInit(false);						//no se dibujan los ejes de coordenadas
	char caracter;						//caracter para pulsar intro al final del juego
	int opcion;							//opcion
    bool fin = false;					//booleano que se pone a cierto cuando el usuario elige la opcion salir
    tSudoku sudo;						//estructura con el sudoku
    ifstream fInSudoku, fInSolucion, fRegiones;				//para leer los archivos con el sudoku inicial, solucion y mapa de regiones
	abrirArchivos (fInSudoku, fInSolucion, fRegiones);			//lectura de dichos archivos
    inicializarTableros (fInSudoku, fInSolucion, sudo, fin);	//inicializacion de los elementos del struct
	inicializarCoordenadas (sudo);								//		inicializacion del array con coordenadas
	inicializa_regiones (sudo, fRegiones);						//		inicializacion del array que indica las casillas que tiene cada region
    if (fin) cout << "ERROR, el sudoku inicial contiene errores.\n";
	else dibuja_todo(sudo);		//ponemos el else para que no dibuje el sudoku en caso de que halla error en los archivos iniciales
	while (!fin){
        limpiar();
        opcion = mostrarMenu();
		limpiar();
		if (opcion == 0) fin = true;
		else if (opcion == 1) opcion1(sudo);
		else if (opcion == 2) opcion2(sudo);
		else if (opcion == 3) opcion3(sudo);
		else if (opcion == 4) opcion4(sudo);
		else if (opcion == 5) opcion5(sudo);
		else if (opcion == 6) opcion6(sudo);
		else cout << "Opcion no valida! Introduzcala de nuevo.\n";
		if (sudo.contador == 81){
			cout << "\nENHORABUENA HAS TERMINADO EL SUDOKU!!!!!!!!\n" << "Pulsa intro para acabar: ";
			cin.get(caracter);
			fin = true;
		}
    }
	vgEnd();
	return 0;
}